#include "warrior.h"
#include "engine.h"
#include "texturemanager.h"
#include "animation.h"
#include "input.h"
#include <cassert>
#include "Collider.h"
#include "CollisionHandler.h"
#include "SDL3/SDL.h"
#include <iostream>
#define GREEN {0x00, 255, 0x00, 0x00}
#define TURQOISE {64, 224, 208, 0}
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
    string coords = to_string(int(m_Transform->X)) + "," + to_string(int(m_Transform->Y));
    TextureManager::GetInstance()->LoadText("COORDS", coords, GREEN);
    TextureManager::GetInstance()->Draw("COORDS", 600, 0, 150, 50);
    SDL_FRect box = m_Collider->GetBox();
    string coords2 = to_string(int(box.x)) + "," + to_string(int(box.y));
    TextureManager::GetInstance()->LoadText("COORDS2", coords2, GREEN);
    TextureManager::GetInstance()->Draw("COORDS2", 600, 50, 150, 50);
    /*TextureManager::GetInstance()->Draw("ACCELX", 0, 0, 500, 50);
    TextureManager::GetInstance()->Draw("ACCELY", 0, 50, 500, 50);
    TextureManager::GetInstance()->Draw("VEL", 0, 100, 500, 50);
    TextureManager::GetInstance()->Draw("POS", 0, 150, 500, 50);
    TextureManager::GetInstance()->Draw("SAFEX", 0, 200, 500, 50);
    TextureManager::GetInstance()->Draw("SAFEY", 0, 250, 500, 50);*/
    TextureManager::GetInstance()->Draw("MOVEKEY", 0, 500, 100, 100);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0x00, 255, 0x00, 0x00);
    if(SDL_RenderRect(Engine::GetInstance()->GetRenderer(), &box) == false) cout << "SDL_RenderRect() == false\n";
}

void Warrior::Update(float dt){
    idle = true;
    m_RigidBody->UnSetForce();
    TextureManager::GetInstance()->Drop("MOVEKEY");
    
    /*if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        if(InputHandler::GetInstance()->Down(SDL_SCANCODE_A)){
            InputHandler::GetInstance()->Push(SDL_SCANCODE_A);
            InputHandler::GetInstance()->buffer.append("A");
        }
    }
    if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        InputHandler::GetInstance()->Push(SDL_SCANCODE_D);
        InputHandler::GetInstance()->buffer.append("D");
    }
    if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_W)){
        InputHandler::GetInstance()->Push(SDL_SCANCODE_W);
        InputHandler::GetInstance()->buffer.append("W");
    }
    if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_S)){
        InputHandler::GetInstance()->Push(SDL_SCANCODE_S);
        InputHandler::GetInstance()->buffer.append("S");
    }*/

    if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        if(!InputHandler::GetInstance()->m_KeyStates[SDL_SCANCODE_D] && !InputHandler::GetInstance()->m_KeyStates[SDL_SCANCODE_W] && !InputHandler::GetInstance()->m_KeyStates[SDL_SCANCODE_S]){
            //TextureManager::GetInstance()->LoadText("MOVEKEY", "A", TURQOISE);
            m_RigidBody->ApplyForceX(-150);
            orient = 2;
            idle = false;
            m_Animation->SetProps(m_TextureID, 2, 4, 128);
        }
    }
    if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        if(!InputHandler::GetInstance()->m_KeyStates[SDL_SCANCODE_A] && !InputHandler::GetInstance()->m_KeyStates[SDL_SCANCODE_W] && !InputHandler::GetInstance()->m_KeyStates[SDL_SCANCODE_S]){
            //TextureManager::GetInstance()->LoadText("MOVEKEY", "D", TURQOISE);
            m_RigidBody->ApplyForceX(150);
            orient = 3;
            idle = false;
            m_Animation->SetProps(m_TextureID, 3, 4, 128);
        }
    }
    if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_W)){
        if(!InputHandler::GetInstance()->m_KeyStates[SDL_SCANCODE_A] && !InputHandler::GetInstance()->m_KeyStates[SDL_SCANCODE_D] && !InputHandler::GetInstance()->m_KeyStates[SDL_SCANCODE_S]){
            //TextureManager::GetInstance()->LoadText("MOVEKEY", "W", TURQOISE);
            m_RigidBody->ApplyForceY(-150);
            orient = 4;
            idle = false;
            m_Animation->SetProps(m_TextureID, 4, 4, 128);
        }
    }
    if(InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_S)){
        if(!InputHandler::GetInstance()->m_KeyStates[SDL_SCANCODE_A] && !InputHandler::GetInstance()->m_KeyStates[SDL_SCANCODE_D] && !InputHandler::GetInstance()->m_KeyStates[SDL_SCANCODE_W]){
            //TextureManager::GetInstance()->LoadText("MOVEKEY", "S", TURQOISE);
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
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox())){
        m_Transform->X = m_LastSafePosition.X;
        m_Collider->Set(m_Transform->X + 7, m_Transform->Y + 7, boxsize, boxsize);
    }

    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X + 7, m_Transform->Y + 7, boxsize, boxsize);

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->GetBox())){
        m_Transform->Y = m_LastSafePosition.Y;
        m_Collider->Set(m_Transform->X + 7, m_Transform->Y + 7, boxsize, boxsize);
    }

    if(idle == false) m_Animation->Update();
}

void Warrior::Clean(){
    TextureManager::GetInstance()->Clean();
}
