#include "MapParser.h"
#include <string>
#include "tinyxml.h"

MapParser* MapParser::instance = nullptr;

bool MapParser::Load(){
    return Parse("L1", "../maps/mapB.tmx");
}

bool MapParser::Parse(string id, string src){
    TiXmlDocument xml;
    xml.LoadFile(src);
    if(xml.Error()){
        cout << "Failed to load " << src << endl;
        cout << xml.ErrorDesc() << endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    int rowcount, columncount, tilesize = 0;
    root->Attribute("width", &columncount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);

    TilesetList tilesets;
    for(TiXmlElement* e = root->FirstChildElement(); e!= nullptr; e = e->NextSiblingElement()){
//        cout << e->Attribute("name");
        if (e->Value() == string("tileset"))
            tilesets.push_back(ParseTileset(e));
    }

    GameMap* gamemap = new GameMap();
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
        if(e->Value() == string("layer")){
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, columncount);
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }

    m_MapDict[id] = gamemap;
    return true;
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset){
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.FirstID);

    xmlTileset->Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.ColumnCount);
    tileset.RowCount = tileset.TileCount / tileset.ColumnCount;
    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");
    return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int columncount){
    TiXmlElement* data;
    for(TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
        if(e->Value() == string("data")){
            data = e;
            break;
        }
    }

    string matrix = data->GetText();
    istringstream iss(matrix);
    string id;

    TileMap tilemap(rowcount, vector<int>(columncount, 0));
    for(int row = 0; row < rowcount; row++){
        for(int col = 0; col < columncount; col++){
            getline(iss, id, ',');
            int q = stoi(id);
            //q = q - 1;
            id = to_string(q);
            stringstream converter(id);
            converter >> tilemap[row][col];

            if(!iss.good()) break;
        }
    }

    return (new TileLayer(tilesize, rowcount, columncount, tilemap, tilesets));
}

bool MapParser::Clean(){
    map<string, GameMap*>::iterator it;
    for(it = m_MapDict.begin()  ; it != m_MapDict.end(); it++)
        it->second = nullptr;
    
    m_MapDict.clear();  
    return true;
}