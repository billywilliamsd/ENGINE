#ifndef ENGINE_H
#define ENGINE_H
#include <SDL3/SDL.h>

class Engine{
    Engine();
    static Engine* instance;
    bool m_IsRunning;
    SDL_Window* w;
    SDL_Renderer* r;
public:
    static Engine* GetInstance(){
        return instance = (instance != nullptr)? instance:new Engine();
    }

    bool Init();
    bool Clean();
    void Quit();

    void Update();
    void Render();
    void Events();

    inline bool IsRunning(){return m_IsRunning;}
    inline SDL_Renderer* GetRenderer(){return r;}
};

#endif