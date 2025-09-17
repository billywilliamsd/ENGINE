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

    cout << "SDL_SCANCODE_A == " << SDL_SCANCODE_A << endl;
    cout << "SDL_SCANCODE_D == " << SDL_SCANCODE_D << endl;
    cout << "SDL_SCANCODE_W == " << SDL_SCANCODE_W << endl;
    cout << "SDL_SCANCODE_S == " << SDL_SCANCODE_S << endl;

    InputHandler::GetInstance()->Push(SDL_SCANCODE_A);
    InputHandler::GetInstance()->Push(SDL_SCANCODE_D);
    InputHandler::GetInstance()->Push(SDL_SCANCODE_W);
    InputHandler::GetInstance()->Push(SDL_SCANCODE_S);

    InputHandler::GetInstance()->GetList();
    //InputHandler::GetInstance()->PrintList();

    while(Engine::GetInstance()->IsRunning()){
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();
    return 0;
}