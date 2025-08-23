#include "input.h"
#include "engine.h"

Input* Input::s_Instance = nullptr;
InputManager* InputManager::instance = nullptr;

Input::Input(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::Listen(){
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

bool Input::GetKeyDown(SDL_Scancode key){
    return m_KeyStates[key] == 1;
}

void Input::KeyUp(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}