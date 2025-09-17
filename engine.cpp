#include "engine.h"
#include "texturemanager.h"
#include "warrior.h"
#include "input.h"
#include "timer.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <cassert>
#include <string>
#include "MapParser.h"
#define BLACK {0x00, 0x00, 0x00}
#define GREEN {0x00, 255, 0x00, 0x00}
#define ORANGE {255, 40, 0, 0}
#define TURQOISE {64, 224, 208, 0}
using namespace std;

Engine* Engine::instance = nullptr;
Warrior* player = nullptr;
TTF_Font* f = nullptr;

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

    w = SDL_CreateWindow("engine", 960, 640, 0);
    if(w == nullptr){
        SDL_Log("Failed to create window: %s\n", SDL_GetError());
        return false;
    }

    r = SDL_CreateRenderer(w, nullptr);
    if(r == nullptr){
        SDL_Log("Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }

    if(SDL_SetRenderVSync(r, 1) == false){
        SDL_Log("Could not enable VSync! SDL error: %s\n", SDL_GetError());
        return false;
    }

    if(!MapParser::GetInstance()->Load()){
        cout << "Failed to load map!" << endl;
    }
    m_LevelMap = MapParser::GetInstance()->GetMap("L1");

    string path = "../Ubuntu-L.ttf";
    f = TTF_OpenFont(path.c_str(), 28);
    if(f == nullptr){
        SDL_Log( "Could not load %s! SDL_ttf Error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }

    player = new Warrior(new Properties("player", 150, 150, 64, 64));
    if(!TextureManager::GetInstance()->Load("player", "../texturebin/sprite.png"))
        assert(0);

    TextureManager::GetInstance()->LoadText("WW", "W", ORANGE);

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
    m_IsRunning = false;
}

void Engine::Update(){
    //float dt = Timer::GetInstance()->GetDeltaTime();
    player->Update(0.2f);
    m_LevelMap->Update();
}

void Engine::Render(){
    SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(r);
    m_LevelMap->Render();
    player->Draw();
    //TextureManager::GetInstance()->LoadText("KEYS", InputHandler::GetInstance()->buffer, TURQOISE);
    //TextureManager::GetInstance()->Draw("KEYS", 700, 500, 200, 100);
    //TextureManager::GetInstance()->Draw("WW", 0, 450, 100, 100);
    TextureManager::GetInstance()->Draw("KEYLIST", 0, 500, 100, 50);
    SDL_RenderPresent(r);
}

void Engine::Events(){
    InputHandler::GetInstance()->Listen();
}