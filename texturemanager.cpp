#include "texturemanager.h"
#include <SDL3_image/SDL_image.h>
#include "engine.h"
#include <iostream>
using namespace std;

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager(){}

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

void TextureManager::Drop(string id){
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}
void TextureManager::Clean(){
    map<string, SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);

    m_TextureMap.clear();
}

void TextureManager::Draw(string id, int x, int y, int width, int height, SDL_FlipMode flip){
    SDL_FRect src = {0, 0, width, height};
    SDL_FRect dst = {x, y, width, height};
    SDL_RenderTextureRotated(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &src, &dst, 0, nullptr, flip);
}

void TextureManager::DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_FlipMode flip){
    SDL_FRect src = {width*frame, height*(row - 1), width, height};
    SDL_FRect dst = {x, y, width, height};
    //cout << "TextureManager::DrawFrame(" << id << ", " << x << ", " << y << ", " << width << ", " << height << ", " << row << ", " << frame << ", " << flip << endl;
    SDL_RenderTextureRotated(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &src, &dst, 0, nullptr, flip);
}