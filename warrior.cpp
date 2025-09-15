#include "warrior.h"
#include "engine.h"
#include "texturemanager.h"
#include "animation.h"
#include "input.h"
#include "Collider.h"
#include "CollisionHandler.h"
#include "SDL3/SDL.h"
#include <iostream>
using namespace std;

int boxsize = 50;

Warrior::Warrior(Properties* p) : Character(p){
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    idle = true;
    orient = 1;
    m_Collider = new Collider();
    m_Collider->Set(150, 150, 50, 50);
    m_Collider->SetBuffer(0, 0, 0, 0);
}

void Warrior::Draw(){
    if(idle == false) m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
    else TextureManager::GetInstance()->DrawFrame("player", m_Transform->X, m_Transform->Y, m_Width, m_Height, orient, 0);
    SDL_FRect box = m_Collider->GetBox();
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0x00, 255, 0x00, 0x00);
    if(SDL_RenderRect(Engine::GetInstance()->GetRenderer(), &box) == false) cout << "SDL_RenderRect() == false\n";
}

void Warrior::Update(float dt){
    idle = true;
    m_RigidBody->UnSetForce();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        if(!Input::GetInstance()->m_KeyStates[SDL_SCANCODE_D] && !Input::GetInstance()->m_KeyStates[SDL_SCANCODE_W] && !Input::GetInstance()->m_KeyStates[SDL_SCANCODE_S]){
            m_RigidBody->ApplyForceX(-150);
            orient = 2;
            idle = false;
            m_Animation->SetProps(m_TextureID, 2, 4, 128);
        }
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        if(!Input::GetInstance()->m_KeyStates[SDL_SCANCODE_A] && !Input::GetInstance()->m_KeyStates[SDL_SCANCODE_W] && !Input::GetInstance()->m_KeyStates[SDL_SCANCODE_S]){
            m_RigidBody->ApplyForceX(150);
            orient = 3;
            idle = false;
            m_Animation->SetProps(m_TextureID, 3, 4, 128);
        }
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)){
        if(!Input::GetInstance()->m_KeyStates[SDL_SCANCODE_A] && !Input::GetInstance()->m_KeyStates[SDL_SCANCODE_D] && !Input::GetInstance()->m_KeyStates[SDL_SCANCODE_S]){
            m_RigidBody->ApplyForceY(-150);
            orient = 4;
            idle = false;
            m_Animation->SetProps(m_TextureID, 4, 4, 128);
        }
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)){
        if(!Input::GetInstance()->m_KeyStates[SDL_SCANCODE_A] && !Input::GetInstance()->m_KeyStates[SDL_SCANCODE_D] && !Input::GetInstance()->m_KeyStates[SDL_SCANCODE_W]){
            m_RigidBody->ApplyForceY(150);
            orient = 1;
            idle = false;
            m_Animation->SetProps(m_TextureID, 1, 4, 128);
        }
    }

    m_RigidBody->Update(dt);

    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X + 7, m_Transform->Y + 7, boxsize, boxsize);
    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox())) m_Transform->X = m_LastSafePosition.X;

    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X + 7, m_Transform->Y + 7, boxsize, boxsize);
    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox())) m_Transform->Y = m_LastSafePosition.Y;
    //m_Transform->TranslateX(m_RigidBody->Position().X);
    //m_Transform->TranslateY(m_RigidBody->Position().Y);

    if(idle == false) m_Animation->Update();
}

void Warrior::Clean(){
    TextureManager::GetInstance()->Clean();
}
