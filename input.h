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
typedef Key* MovementKeys;

class InputHandler{
    InputHandler();
    static InputHandler* s_Instance;
    void KeyUp();
    void KeyDown();

    string List;
    MovementKeys L;
    void PushKeys(int n, Key* g);
    void PrintKeys(Key* g);
    void RemoveKeys(int n, Key* g);
    void GetListItem(Key* g);
    bool IsDown(int n, Key* g);
    string GetChar(int n);
public:
    static InputHandler* GetInstance(){return s_Instance = (s_Instance != nullptr) ? s_Instance : new InputHandler();}
    void Listen();
    bool GetKeyDown(SDL_Scancode key);
    void GetList();
    void PrintList(){cout << "List == " << List << endl;}
    int GetKey(int n);
    
    void Push(int n);
    void Print();
    void Remove(int n);
    bool Down(int n);

    const bool* m_KeyStates;
};
#endif