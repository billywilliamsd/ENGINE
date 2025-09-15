#ifndef TILELAYER_H
#define TILELAYER_H
#include "layer.h"
#include <string>
#include <vector>
using namespace std;

struct Tileset{
    int FirstID, LastID;
    int RowCount, ColumnCount;
    int TileCount, TileSize;
    string Name, Source;
};
using TilesetList = vector<Tileset>;
using TileMap = vector<vector<int> >;

class TileLayer : public Layer{
    int m_TileSize;
    int m_RowCount, m_ColumnCount;
    TileMap m_TileMap;
    TilesetList m_Tilesets;
public:
    TileLayer(int tilesize, int rowcount, int columncount, TileMap tilemap, TilesetList tilesets);
    virtual void Render();
    virtual void Update();
    inline TileMap GetTileMap(){return m_TileMap;}
};
#endif