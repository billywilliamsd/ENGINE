#include "engine.h"
#include "timer.h"
#include "texturemanager.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <iostream>
using namespace std;

TTF_Font* gFont;

int main(int argc, char** argv){
    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunning()){
        Uint64 framestart = SDL_GetTicksNS();
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();

        Uint64 frametime = SDL_GetTicksNS() - framestart;
        Uint64 nsperframe = 1000000000.0 / 60;
        if(frametime < nsperframe){
            Uint64 sleeptime = nsperframe - frametime;
            SDL_DelayPrecise(nsperframe - frametime);
            frametime = SDL_GetTicksNS() - framestart;
            double fps = 1000000000.0 / frametime;
            string fpsdisplay = "frames per second: ";
            fpsdisplay.append(to_string(fps));
            TextureManager::GetInstance()->LoadText("FPS", fpsdisplay, {0x00, 0x00, 0x00, 0x00});
        }
    }

    Engine::GetInstance()->Clean();
    return 0;
}