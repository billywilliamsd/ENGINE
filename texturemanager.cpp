#include "texturemanager.h"
#include <SDL3_image/SDL_image.h>
#include "engine.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <cassert>
#include <iostream>
using namespace std;

extern TTF_Font* f;

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

bool TextureManager::LoadText(string id, string t, SDL_Color c){
    SDL_DestroyTexture(m_TextureMap[id]);
    SDL_Surface* s = TTF_RenderText_Blended(f, t.c_str(), 0, c);
    if(s == nullptr){
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", SDL_GetError());
        return false;
    }
    
    SDL_Texture* tx = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), s);
    if(tx == nullptr){
        SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = tx;
    SDL_DestroySurface(s);
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
    SDL_RenderTextureRotated(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &src, &dst, 0, nullptr, flip);
}

void TextureManager::DrawTile(string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_FlipMode flip){
    SDL_FRect dst = {x, y, tilesize, tilesize};
    SDL_FRect src = {tilesize * frame, tilesize * (row), tilesize, tilesize};
    SDL_RenderTextureRotated(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &src, &dst, 0, 0, flip);
}