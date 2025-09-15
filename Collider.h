#ifndef COLLIDER_H
#define COLLIDER_H
#include <SDL3/SDL.h>

class Collider{
    SDL_FRect m_Box;
    SDL_FRect m_Buffer;
public:
    inline SDL_FRect GetBox(){return m_Box;}
    inline void SetBuffer(float x, float y, float w, float h){m_Buffer = {x, y, w, h};}

    void Set(float x, float y, float w, float h){
        m_Box = {x - m_Buffer.x,
            y - m_Buffer.y,
            w - m_Buffer.w,
            h - m_Buffer.h
        };
    }
};
#endif