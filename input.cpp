#include "input.h"
#include "engine.h"
#include "texturemanager.h"
#include <cassert>
#include <string>
#include <iostream>
#define GREEN {0x00, 255, 0x00, 0x00}
#define ORANGE {255, 40, 0, 0}
using namespace std;

InputHandler* InputHandler::s_Instance = nullptr;

InputHandler::InputHandler() : L(nullptr){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

//A - 97 - 4
//D - 100 - 26
//W - 119 - 7
//S - 115 - 22
void InputHandler::Listen(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_EVENT_QUIT:
            Engine::GetInstance()->Quit();
            break;
        case SDL_EVENT_KEY_DOWN:
            KeyDown();
            break;
        case SDL_EVENT_KEY_UP:
            KeyUp();
            break;
        }

    }

}

bool InputHandler::GetKeyDown(SDL_Scancode key){
    return m_KeyStates[key] == 1;
}


void InputHandler::KeyUp(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
    if(m_KeyStates[SDL_SCANCODE_W] == 0){
        TextureManager::GetInstance()->LoadText("WW", "W", ORANGE);
    }

}

void InputHandler::KeyDown(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
    if(m_KeyStates[SDL_SCANCODE_W]){
        TextureManager::GetInstance()->LoadText("WW", "W", GREEN);
    }
}

void InputHandler::Push(int n){
    cout << "Push(" << n << ")\n";
    if (Down(n)) {
        cout << "\tDown(" << n << ") returned true, duplicate found, returning..." << endl;
        return;
    }
    if (L == nullptr) {
        cout << "\tL is empty, putting {" << GetChar(n) << "} in 1st slot" << endl;
        L = new Key{ n, nullptr };
    }
    else PushKeys(n, L);
}

void InputHandler::PushKeys(int n, Key* g){
    cout << "PushKeys(" << n << "," << "-" << ")" << endl;
    if (g->next == nullptr) {
        cout << "\tg->next == nullptr, putting {" << GetChar(n) << "} in g->next" << endl;
        g->next = new Key{ n, nullptr };
    }
    else PushKeys(n, g->next);
}

void InputHandler::Print(){
    if (L == nullptr) return;
    PrintKeys(L);
    cout << endl;
}

void InputHandler::PrintKeys(Key* g){
    cout << g->code << endl;
    if (g->next == nullptr) return;
    PrintKeys(g->next);
}

void InputHandler::Remove(int n){
    if(L == nullptr) return;
    if(L->code == n){
        if(L->next == nullptr){
            delete(L);
            return;
        }
        Key* temp = L->next;
        delete(L);
        L = temp;
        return;
    }
    
    RemoveKeys(n, L);
}

void InputHandler::RemoveKeys(int n, Key* g){
    if(g->next->code == n){
        if(g->next->next == nullptr){
            delete(g->next);
            g->next = nullptr;
            return;
        }
        Key* temp = g->next->next;
        delete(g->next);
        g->next = temp;
        return;
    }
}

void InputHandler::GetList(){
    if(L == nullptr) return;
    cout << "L->code == " << L->code << endl;
    const string c = GetChar(L->code);
    List.assign(c);
    cout << "\tList == " << List << endl;
    GetListItem(L->next);
}

void InputHandler::GetListItem(Key* g){
    if (g == nullptr) {
        cout << "g == nullptr\n\t";
        cout << "List == " << List << endl;
        return;
    }
    else {
        cout << "g->code == " << g->code << endl;
    }
    List.append(" << ");
    const string c = GetChar(g->code);
    List.append(c);
    cout << "\tList == " << List << endl;
    GetListItem(g->next);
}

int InputHandler::GetKey(int n){
    switch(n){
    case SDL_SCANCODE_A: return 4;
    case SDL_SCANCODE_D: return 26;
    case SDL_SCANCODE_W: return 7;
    case SDL_SCANCODE_S: return 22;
    default: assert(0);
    }
}


bool InputHandler::Down(int n){
    cout << "Down(" << n << ")\n";
    if (L == nullptr) return false;
    if (L->code == GetKey(n)) return true;
    else return IsDown(n, L->next);
}

bool InputHandler::IsDown(int n, Key* g){
    cout << "\tIsDown(" << n << ")\n";
    if (g == nullptr) {
        cout << "\t\treturning false\n";
        return false;
    }
    if (g->code == GetKey(n)) {
        cout << "\t\treturning true\n";
        return true;
    }
    else return IsDown(n, g->next);
}

string InputHandler::GetChar(int n){
    string s = "";
    switch(n){
    case SDL_SCANCODE_A: {
        s.push_back('A');
        return s;
    }
    case SDL_SCANCODE_D: {
        s.push_back('D');
        return s;
    }
    case SDL_SCANCODE_W: {
        s.push_back('W');
        return s;
    }
    case SDL_SCANCODE_S: {
        s.push_back('S');
        return s;
    }
    default: assert(0);
    }
}