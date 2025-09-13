#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <vector>
#include "layer.h"
using namespace std;

class GameMap{
    vector<Layer*> m_MapLayers;
public:
    virtual void Render(){
        for(unsigned int i = 0; i < m_MapLayers.size(); i++){
            m_MapLayers[i]->Render();
        }
    }
    
    virtual void Update(){
        for(unsigned int i = 0; i < m_MapLayers.size(); i++){
            m_MapLayers[i]->Update();
        }
    }

    friend class MapParser;
    vector<Layer*> GetMapLayers(){return m_MapLayers;}
};

#endif