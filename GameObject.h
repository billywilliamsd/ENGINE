#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "IObject.h"
#include "transform.h"
#include <SDL3/SDL.h>

struct Properties{
public:
    string TextureID;
    int Width, Height;
    float X, Y;
    SDL_FlipMode Flip;

    Properties(string textureID, int x, int y, int width, int height, SDL_FlipMode flip = SDL_FLIP_NONE){
        X = x;
        Y = y;
        Flip = flip;
        Width = width;
        Height = height;
        TextureID = textureID;
    }
};

class GameObject : public IObject{
public:
    GameObject(Properties* p):m_TextureID(p->TextureID),
        m_Width(p->Width),
        m_Height(p->Height),
        m_Flip(p->Flip){
            m_Transform = new Transform(p->X, p->Y);
        }

    virtual void Draw() = 0;
    virtual void Clean() = 0;
    virtual void Update(float dt) = 0;
protected:
    Transform* m_Transform;
    int m_Width, m_Height;
    string m_TextureID;
    SDL_FlipMode m_Flip;
};

#endif