#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H
#include "tilelayer.h"
#include <SDL3/SDL.h>
class CollisionHandler{
    CollisionHandler();
    TileMap m_CollisionTilemap;
    TileLayer* m_CollisionLayer;
    static CollisionHandler* instance;
public:
    inline static CollisionHandler* GetInstance(){return instance = (instance == nullptr) ? new CollisionHandler() : instance;}
    bool MapCollision(SDL_FRect a);
    bool CheckCollision(SDL_FRect a, SDL_FRect b);  
};
#endif