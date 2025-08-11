#include "texturemanager.h"
#include <SDL3_image/SDL_image.h>
#include "engine.h"
using namespace std;

TextureManager* TextureManager::instance = nullptr;

bool TextureManager::Load(string id, string file){
    SDL_Surface* s = IMG_Load(file.c_str());
    if(s == nullptr){
        SDL_Log("Failed to load texture: %s, %s\n", file.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* t = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), s);
    if(t == nullptr){
        SDL_Log("Failed to create texture from surface: %s\n", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = t;
    return true;
}

void TextureManager::Drop(string id){}
void TextureManager::Clean(){}

void TextureManager::Draw(string id, int x, int y, int width, int height, SDL_FlipMode flip){
    SDL_FRect src = {0, 0, width, height};
    SDL_FRect dst = {x, y, width, height};
    SDL_RenderTextureRotated(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &src, &dst, 0, nullptr, flip);
}