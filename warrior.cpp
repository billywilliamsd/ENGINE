#include "warrior.h"
#include "texturemanager.h"
#include "animation.h"
#include "SDL3/SDL.h"
#include <iostream>
using namespace std;

Warrior::Warrior(Properties* p) : Character(p){
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 4, 128, SDL_FLIP_HORIZONTAL);
}

void Warrior::Draw(){
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt){
    m_RigidBody->Update(0.2);
    m_Transform->TranslateX(m_RigidBody->Position().X);
    m_Transform->TranslateY(m_RigidBody->Position().Y);
    m_Animation->Update();
}

void Warrior::Clean(){
    TextureManager::GetInstance()->Clean();
}
