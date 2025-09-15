#include "CollisionHandler.h"
#include "engine.h"
#include <iostream>
using namespace std;

CollisionHandler* CollisionHandler::instance = nullptr;

CollisionHandler::CollisionHandler(){
    m_CollisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().back();
    m_CollisionTilemap = m_CollisionLayer->GetTileMap();
}

bool CollisionHandler::CheckCollision(SDL_FRect a, SDL_FRect b){
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return x_overlaps && y_overlaps;
}

bool CollisionHandler::MapCollision(SDL_FRect a){
    int tileSize = 32;
    int RowCount = 100;
    int ColumnCount = 100;

    int left_tile = a.x / tileSize;
    int right_tile = (a.x + a.w) / tileSize;

    int top_tile = a.y / tileSize;
    int bottom_tile = (a.y + a.h) / tileSize;

    if(left_tile < 0) left_tile = 0;
    if(right_tile > ColumnCount) right_tile = ColumnCount;

    if(top_tile < 0) top_tile = 0;
    if(bottom_tile > RowCount) bottom_tile = RowCount;

    for(int i = left_tile; i <= right_tile; i++){
        for(int j = top_tile; j <= bottom_tile; j++){
            if(m_CollisionTilemap[j][i] > 0) return true;
        }
    }

    return false;
}