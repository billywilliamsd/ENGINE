#include "warrior.h"
#include "texturemanager.h"
#include "animation.h"
#include "SDL3/SDL.h"
#include <iostream>
using namespace std;

Warrior::Warrior(Properties* p) : Character(p){
    m_Animation->SetProps(p->TextureID, 1, 4, 128, SDL_FLIP_HORIZONTAL);
}

void Warrior::Draw(){
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
    //TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame);
}

void Warrior::Update(float dt){
    m_Animation->Update();
}

void Warrior::Clean(){
    TextureManager::GetInstance()->Clean();
}
