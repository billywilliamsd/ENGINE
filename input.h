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

class InputManager{
    InputManager(){
        a_isdown = false;
        d_isdown = false;
        w_isdown = false;
        s_isdown = false;
        a_tick = 0;
        d_tick = 0;
        w_tick = 0;
        s_tick = 0;
    }
    static InputManager* instance;
public:
    static InputManager* GetInstance(){return instance = (instance == nullptr) ? new InputManager() : instance;}

    bool a_isdown;
    Uint64 a_tick;
    bool d_isdown;
    Uint64 d_tick;
    bool w_isdown;
    Uint64 w_tick;
    bool s_isdown;
    Uint64 s_tick;
};

#endif