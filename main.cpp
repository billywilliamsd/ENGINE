#include "engine.h"
#include "timer.h"
#include "texturemanager.h"
#include "input.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <iostream>
using namespace std;

TTF_Font* gFont;


int main(int argc, char** argv){
    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunning()){
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();
    return 0;
}