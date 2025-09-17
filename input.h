#ifndef INPUT_H
#define INPUT_H
#include <string>
#include <SDL3/SDL.h>

struct Key{
    int code;
    Key* next;
};
typedef Key* MovementKeys;

class InputHandler{
    InputHandler();
    MovementKeys L;
    static InputHandler* s_Instance;

    void KeyUp();
    void KeyDown();

    void PushKeys(int n, Key* g);
    void PrintKeys(Key* g);
    void RemoveKeys(int n, Key* g);
    bool IsDown(int n, Key* g);
public:
    static InputHandler* GetInstance(){return s_Instance = (s_Instance != nullptr) ? s_Instance : new InputHandler();}
    
    void Listen();
    bool GetKeyDown(SDL_Scancode key);
    
    void Push(int n);
    void Print();
    void Remove(int n);
    bool Down(int n);
    
    const bool* m_KeyStates;
};
#endif