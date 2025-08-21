#include "engine.h"
#include "texturemanager.h"
#include "warrior.h"
#include "input.h"
#include <iostream>
#include <cassert>
using namespace std;

Engine* Engine::instance = nullptr;
Warrior* player = nullptr;

Engine::Engine(){}

bool Engine::Init(){
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("%s: %s", "Failed to initialize SDL", SDL_GetError());
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
}

void Engine::Render(){
    SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0x41, 0x00);
    SDL_RenderClear(r);
    TextureManager::GetInstance()->Draw("tree", 0, 0, 50, 50);
    player->Draw();
    SDL_RenderPresent(r);
}

void Engine::Events(){
    Input::GetInstance()->Listen();
}