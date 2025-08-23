#include "engine.h"
#include "texturemanager.h"
#include "warrior.h"
#include "input.h"
#include "text.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <cassert>
#include <string>
#define BLACK {0x00, 0x00, 0x00}
using namespace std;

Engine* Engine::instance = nullptr;
Warrior* player = nullptr;
TTF_Font* f = nullptr;
InputText* SCANCODE_A = new InputText();
InputText* SCANCODE_D = new InputText();
InputText* SCANCODE_W = new InputText();
InputText* SCANCODE_S = new InputText();
Text* A_TICK = new Text();

Engine::Engine(){}

bool Engine::Init(){
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("%s: %s", "Failed to initialize SDL", SDL_GetError());
        return false;
    }

    if(!TTF_Init()){
        SDL_Log("SDL_ttf could not initialize! SDL_ttf error: %s\n", SDL_GetError());
        return false;
    }

    w = SDL_CreateWindow("engine", 900, 600, 0);
    if(w == nullptr){
        SDL_Log("Failed to create window: %s\n", SDL_GetError());
        return false;
    }

    r = SDL_CreateRenderer(w, nullptr);
    if(r == nullptr){
        SDL_Log("Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }

    string path = "../Ubuntu-L.ttf";
    f = TTF_OpenFont(path.c_str(), 28);
    if(f == nullptr){
        SDL_Log( "Could not load %s! SDL_ttf Error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }

    if(!SCANCODE_A->loadFromRenderedText("SDL_SCANCODE_A", BLACK)){
        SDL_Log("Could not load text texture %s! SDL_ttf Error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }
    if(!SCANCODE_D->loadFromRenderedText("SDL_SCANCODE_D", BLACK)){
        SDL_Log("Could not load text texture %s! SDL_ttf Error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }
    if(!SCANCODE_W->loadFromRenderedText("SDL_SCANCODE_W", BLACK)){
        SDL_Log("Could not load text texture %s! SDL_ttf Error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }
    if(!SCANCODE_S->loadFromRenderedText("SDL_SCANCODE_S", BLACK)){
        SDL_Log("Could not load text texture %s! SDL_ttf Error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }
    if(!A_TICK->loadFromRenderedText(" ", BLACK)){
        SDL_Log("Could not load text texture %s! SDL_ttf Error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }

    bool loaded = TextureManager::GetInstance()->Load("tree", "../texturebin/tree.png");
    if(loaded == false) assert(0);

    player = new Warrior(new Properties("player", 150, 150, 64, 64));
    bool loaded2 = TextureManager::GetInstance()->Load("player", "../texturebin/sprite.png");
    if(loaded2 == false) assert(0);


    m_IsRunning = true;
    return true;
}

bool Engine::Clean(){
    TextureManager::GetInstance()->Clean();
    SDL_DestroyWindow(w);
    SDL_DestroyRenderer(r);
    //IMG_QUIT();
    SDL_Quit();
    return true;
}

void Engine::Quit(){

}


void Engine::Update(){
    player->Update(0);
    TextManager::GetInstance()->Update();
}

void Engine::Render(){
    SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0x41, 0x00);
    SDL_RenderClear(r);
    TextureManager::GetInstance()->Draw("tree", 0, 0, 50, 50);
    player->Draw();
    SCANCODE_A->Render(500, 50);
    if(SCANCODE_A->down) A_TICK->Render(500, 450);
    SCANCODE_D->Render(500, 100);
    SCANCODE_W->Render(500, 150);
    SCANCODE_S->Render(500, 200);
    SDL_RenderPresent(r);
}

void Engine::Events(){
    Input::GetInstance()->Listen();
}