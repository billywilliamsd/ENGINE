#include "input.h"
#include "engine.h"
#include "texturemanager.h"
#include <cassert>
#include <string>
#include <iostream>
#define GREEN {0x00, 255, 0x00, 0x00}
#define ORANGE {255, 40, 0, 0}
using namespace std;

InputQueue* InputQueue::instance = nullptr;
InputHandler* InputHandler::instance = nullptr;

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
    if(m_KeyStates[SDL_SCANCODE_A]){
        InputQueue::GetInstance()->Push(SDL_SCANCODE_A);
    }
    if(m_KeyStates[SDL_SCANCODE_D]){
        InputQueue::GetInstance()->Push(SDL_SCANCODE_D);
    }
    if(m_KeyStates[SDL_SCANCODE_W]){
        InputQueue::GetInstance()->Push(SDL_SCANCODE_W);
    }
    if(m_KeyStates[SDL_SCANCODE_S]){
        InputQueue::GetInstance()->Push(SDL_SCANCODE_S);
    }
    InputQueue::GetInstance()->Print();     
}

void InputQueue::Print(){
    if(q == nullptr) cout << "(empty)\n";
    cout << q->code;
    PrintKey(q->next);
}

void InputQueue::PrintKey(Key* z){
    if(z == nullptr){
        cout << endl;
        return;
    }
    cout << " :: " << z->code;
    PrintKey(z->next);
}

void InputQueue::Push(int n){
    if(Contains(n)) return;
    if(q == nullptr){
        q = new Key{n, nullptr};
        return;
    }
    PushKey(n, q);
}

void InputQueue::PushKey(int n, Key* z){
    if(z->next == nullptr){
        z->next = new Key{n, nullptr};
    }
    else PushKey(n, z->next);
}

bool InputQueue::Contains(int n){
    if(q == nullptr) return false;
    else if(q->code == n) return true;
    else return ContainsIn(n, q->next);
}

bool InputQueue::ContainsIn(int n, Key* z){
    if(z == nullptr) return false;
    if(z->code == n) return true;
    return ContainsIn(n, z->next);

}

void InputQueue::Remove(int n){
    if(q == nullptr) return;
    if(q->code == n){
        if(q->next == nullptr){
            delete(q);
            q = nullptr;
            return;
        }
        Key* temp = q->next;
        delete(q);
        q = temp;
    }
    RemoveKey(n, q);
}

void InputQueue::RemoveKey(int n, Key* z){
    if(z->next == nullptr){
        return;
    }
    if(z->next->code == n){
        if(z->next->next == nullptr){
            delete(z->next);
            z->next = nullptr;
            return;
        }
        else{
            Key* temp = z->next->next;
            delete(z->next);
            z->next = temp;
            return;
        }
    }
    RemoveKey(n, z->next);
}