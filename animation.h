#ifndef ANIMATION_H
#define ANIMATION_H
#include <SDL3/SDL.h>
#include <iostream>
using namespace std;

class Animation{
public:
    void Update();
    void Draw(float x, float y, int spriteWidth, int spriteHeight);
    void SetProps(string textureID, int spriteRow, int frameCount, int animSpeed, SDL_FlipMode flip = SDL_FLIP_NONE);
private:
    int m_SpriteRow, m_SpriteFrame;
    int m_AnimSpeed, m_FrameCount;
    string m_TextureID;
    SDL_FlipMode m_Flip;
};

#endif