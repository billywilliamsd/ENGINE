#ifndef INPUT_H
#define INPUT_H
#include <SDL3/SDL.h>

class Input{
    Input();
    static Input* s_Instance;

    void KeyUp();
    void KeyDown();
public:
    static Input* GetInstance(){return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();}
    
    void Listen();
    bool GetKeyDown(SDL_Scancode key);
    
    const bool* m_KeyStates;
};
#endif