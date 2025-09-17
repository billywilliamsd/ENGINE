#include "input.h"
#include "engine.h"
#include <string>
#include <iostream>
using namespace std;

InputHandler* InputHandler::s_Instance = nullptr;

InputHandler::InputHandler() : L(nullptr){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

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
}

void InputHandler::KeyDown(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void InputHandler::Push(int n){
    if(L == nullptr) L = new Key{n, nullptr};
    else PushKeys(n, L);
}

void InputHandler::PushKeys(int n, Key* g){
    if(g->next == nullptr) g->next = new Key{n, nullptr};
    else PushKeys(n, g->next);
}

void InputHandler::Print(){
    PrintKeys(L);
}

void InputHandler::PrintKeys(Key* g){
    if(g == nullptr) return;
    cout << g->code << endl;
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

bool InputHandler::Down(int n){
    if(L == nullptr) return false;
    else if(L->code == n) return true;
    else return IsDown(n, L->next);
}

bool InputHandler::IsDown(int n, Key* g){
    if(g == nullptr) return false;
    else if(g->code != n) return IsDown(n, g->next);
}
