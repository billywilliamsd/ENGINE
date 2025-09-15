#include "tilelayer.h"
#include "texturemanager.h"
#include <iostream>
using namespace std;

TileLayer::TileLayer(int tilesize, int rowcount, int columncount, TileMap tilemap, TilesetList tilesets) :
    m_TileSize(tilesize), m_RowCount(rowcount), m_ColumnCount(columncount), m_TileMap(tilemap), m_Tilesets(tilesets){
    for(unsigned int i = 0; i < m_Tilesets.size(); i++){
        TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "../maps/" + m_Tilesets[i].Source);
    }
}

void TileLayer::Render(){
    for(unsigned int i = 0; i < m_RowCount; i++){
        for(unsigned int j = 0; j < m_ColumnCount; j++){
            int tileID = m_TileMap[i][j];

            if(tileID == 0) continue;
            else{
                int index = 0;
                if(m_Tilesets.size() > 1){
                    for(unsigned int k = 1; k < m_Tilesets.size(); k++){
                        if(tileID > m_Tilesets[k].FirstID && tileID < m_Tilesets[k].LastID){
                            tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                            index = k;
                            cout << "\t\tm_Tilesets.size() == " << m_Tilesets.size() << "\n\t\tindex == " << k << endl;
                            break;
                        }
                    }
                }
            
                Tileset ts = m_Tilesets[index];
                int tileRow = tileID / ts.ColumnCount;
                int tileCol = tileID - (tileRow * ts.ColumnCount) - 1;

                if(tileID % ts.ColumnCount == 0){
                    tileRow--;
                    tileCol = ts.ColumnCount - 1;
                }
                

                TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, ts.TileSize * j, ts.TileSize * i, tileRow, tileCol);
            }
        }
    }
}

void TileLayer::Update(){}