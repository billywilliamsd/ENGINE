#ifndef MAPPARSER_H
#define MAPPARSER_H
#include <map>
#include <string>
#include "gamemap.h"
#include "tilelayer.h"
#include "tinyxml.h"
using namespace std;

class MapParser{
    static MapParser* instance;
    map<string, GameMap*> m_MapDict;
    bool Parse(string id, string source);
    Tileset ParseTileset(TiXmlElement* xmlTileset);
    TileLayer* ParseTileLayer(TiXmlElement* xmllayer, TilesetList tilesets, int tilesize, int rowcount, int columncount);
public:
    bool Load();
    bool Clean();
    inline GameMap* GetMap(string id){return m_MapDict[id];};
    inline static MapParser* GetInstance(){return instance = (instance == nullptr) ? new MapParser() : instance;}
};
#endif