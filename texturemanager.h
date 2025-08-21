#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <string>
#include <SDL3/SDL.h>
#include <map>
using namespace std;

class TextureManager{
    TextureManager();
    static TextureManager* instance;
    map<string, SDL_Texture*> m_TextureMap;
public:
    static TextureManager* GetInstance(){return instance = (instance != nullptr)? instance: new TextureManager();}
    
    bool Load(string id, string path);
    void Drop(string id);
    void Clean();

    void Draw(string id, int x, int y, int width, int height, SDL_FlipMode flip = SDL_FLIP_NONE);
    void DrawFrame(string id, int x, int y, int width, int height, int row, int frame, SDL_FlipMode flip = SDL_FLIP_NONE);
};
#endif