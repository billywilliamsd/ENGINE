#include "warrior.h"
#include "texturemanager.h"
#include "animation.h"
#include "input.h"
#include "SDL3/SDL.h"
#include <iostream>
using namespace std;

Warrior::Warrior(Properties* p) : Character(p){
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    idle = 1;
    //m_Animation->SetProps(m_TextureID, 3, 4, 128, SDL_FLIP_HORIZONTAL);
}

void Warrior::Draw(){
    if(idle == 0) m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
    else TextureManager::GetInstance()->DrawFrame("player", m_Transform->X, m_Transform->Y, m_Width, m_Height, 1, 0);
}

void Warrior::Update(float dt){
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        cout << "GetKeyDown(SDL_SCANCODE_A) == true\n";
        idle = 0;
        m_Animation->SetProps(m_TextureID, 2, 4, 128);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        idle = 0;
        m_Animation->SetProps(m_TextureID, 3, 4, 128);
        cout << "GetKeyDown(SDL_SCANCODE_D) == true\n";
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)){
        cout << "GetKeyDown(SDL_SCANCODE_W) == true\n";
        idle = 0;
        m_Animation->SetProps(m_TextureID, 4, 4, 128);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)){
        cout << "GetKeyDown(SDL_SCANCODE_S) == true\n";
        idle = 0;
        m_Animation->SetProps(m_TextureID, 1, 4, 128);
    }

    m_RigidBody->Update(0.2);
    m_Transform->TranslateX(m_RigidBody->Position().X);

    if(idle == 0) m_Animation->Update();
}

void Warrior::Clean(){
    TextureManager::GetInstance()->Clean();
}
