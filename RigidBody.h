#ifndef RIGIDBODY
#define RIGIDBODY
#include "vector2d.h"
#include "texturemanager.h"
#define ORANGE {255, 40, 0, 0}

#define UNI_MASS 1.0f
#define GRAVITY 9.8f

class RigidBody{
    float m_Mass;

    Vector2D m_Force;
    Vector2D m_Position;
    Vector2D m_Velocity;
    Vector2D m_Acceleration;
public:
    RigidBody(){
        m_Mass = UNI_MASS;
    }

    inline void SetMass(float mass){m_Mass = mass;}

    inline void ApplyForce(Vector2D F){m_Force = F;}
    inline void ApplyForceX(float Fx){m_Force.X = Fx;}
    inline void ApplyForceY(float Fy){m_Force.Y = Fy;}
    inline void UnSetForce(){m_Force = Vector2D(0, 0);}

    inline float GetMass(){return m_Mass;}
    inline Vector2D Position(){return m_Position;}
    inline Vector2D Velocity(){return m_Velocity;}
    inline Vector2D Acceleration(){return m_Acceleration;}

    void Update(float dt){
        m_Acceleration.X = m_Force.X/m_Mass;
        m_Acceleration.Y = m_Force.Y/m_Mass;
        m_Velocity = m_Acceleration*dt;
        m_Position = m_Velocity*dt;
        TextureManager::GetInstance()->LoadText("ACCELX", "m_Acceleration.X == " + to_string(int(m_Acceleration.X)), ORANGE);
        TextureManager::GetInstance()->LoadText("ACCELY", "m_Acceleration.Y == " + to_string(int(m_Acceleration.Y)), ORANGE);
        TextureManager::GetInstance()->LoadText("VEL", "m_Velocity == (" + to_string(int(m_Velocity.X) ) + "," + to_string(int(m_Velocity.Y)) + ")", ORANGE);
        TextureManager::GetInstance()->LoadText("POS", "m_Position == (" + to_string(int(m_Position.X)) + "," + to_string(int(m_Position.Y)) + ")", ORANGE);
    }
};

#endif