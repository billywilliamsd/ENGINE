#ifndef INPUT_H
#define INPUT_H
#include <string>
#include <SDL3/SDL.h>
#include <iostream>
using namespace std;

struct Key{
    int code;
    Key* next;
};

class InputQueue{
    static InputQueue* instance;
    Key* q;

    void PushKey(int n, Key* z);
    void PrintKey(Key* z);
    bool ContainsIn(int n, Key* z);
    void RemoveKey(int n, Key* z);
public:
    static InputQueue* GetInstance(){return instance = (instance != nullptr) ? instance : new InputQueue();}
    void Render();
    void Print();
    void Push(int n);
    bool Contains(int n);
    void Remove(int n);
    int Pop();
};

class InputHandler{
    InputHandler() { m_KeyStates = new bool[512]; }
    static InputHandler* instance;
    void KeyUp();
    void KeyDown();

public:
    static InputHandler* GetInstance(){return instance = (instance != nullptr) ? instance : new InputHandler();}
    void Listen();
    bool GetKeyDown(SDL_Scancode key);

    const bool* m_KeyStates;
};

#endif