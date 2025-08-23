#include "text.h"
#include "engine.h"
#include "input.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#define BLACK {0, 0, 0}
#define RED {255, 0, 0}
using namespace std;

TextManager* TextManager::instance = nullptr;
extern TTF_Font* f;
extern InputText* SCANCODE_A;
extern InputText* SCANCODE_D;
extern InputText* SCANCODE_W;
extern InputText* SCANCODE_S;
extern Text* A_TICK;

bool Text::loadFromRenderedText(string s, SDL_Color c){
    SDL_Surface* srf = TTF_RenderText_Blended(f, s.c_str(), 0, c);
    if(srf == nullptr){
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", SDL_GetError());
        return false;
    }

    m_Texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), srf);
    if(m_Texture == nullptr){
        SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    m_Width = srf->w;
    m_Height = srf->h;

    SDL_DestroySurface(srf);
    return true;
}

void Text::Render(float x, float y){
    SDL_FRect dst = {x, y, m_Width, m_Height};
    SDL_RenderTextureRotated(Engine::GetInstance()->GetRenderer(), m_Texture, nullptr, &dst, 0, nullptr, SDL_FLIP_NONE);
}

void TextManager::Update(){
    delete SCANCODE_A;
    SCANCODE_A = new InputText();
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        if(SCANCODE_A->down == false){
            SCANCODE_A->down = true;
            SCANCODE_A->tick = SDL_GetTicks();
            A_TICK->loadFromRenderedText(to_string(SCANCODE_A->tick), RED);
        }
        SCANCODE_A->loadFromRenderedText("SDL_SCANCODE_A", RED);
    }
    else{
        SCANCODE_A->down = false;
        SCANCODE_A->loadFromRenderedText("SDL_SCANCODE_A", BLACK);
        SCANCODE_A->tick = 0;
    }

    delete SCANCODE_D;
    SCANCODE_D = new InputText();
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) SCANCODE_D->loadFromRenderedText("SDL_SCANCODE_D", RED);
    else SCANCODE_D->loadFromRenderedText("SDL_SCANCODE_D", BLACK);

    delete SCANCODE_W;
    SCANCODE_W = new InputText();
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) SCANCODE_W->loadFromRenderedText("SDL_SCANCODE_W", RED);
    else SCANCODE_W->loadFromRenderedText("SDL_SCANCODE_W", BLACK);

    delete SCANCODE_S;
    SCANCODE_S = new InputText();
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) SCANCODE_S->loadFromRenderedText("SDL_SCANCODE_S", RED);
    else SCANCODE_S->loadFromRenderedText("SDL_SCANCODE_S", BLACK);
}