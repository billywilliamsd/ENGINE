#ifndef RIGIDBODY
#define RIGIDBODY
#include "vector2d.h"

#define UNI_MASS 1.0f
#define GRAVITY 9.8f

class RigidBody{
    float m_Mass;
    float m_Gravity;

    Vector2D m_Force;
    Vector2D m_Friction;
    Vector2D m_Position;
    Vector2D m_Velocity;
    Vector2D m_Acceleration;
public:
    RigidBody(){
        m_Mass = UNI_MASS;
        m_Gravity = GRAVITY;
    }

    inline void SetMass(float mass){m_Mass = mass;}
    inline void SetGravity(float gravity){m_Gravity = gravity;}

    inline void ApplyForce(Vector2D F){m_Force = F;}
    inline void ApplyForceX(float Fx){m_Force.X = Fx;}
    inline void ApplyForceY(float Fy){m_Force.Y = Fy;}
    inline void UnSetForce(){m_Friction = Vector2D(0, 0);}

    inline void ApplyFriction(Vector2D Fr){m_Friction = Fr;}
    inline void UnSetFriction(){m_Friction = Vector2D(0, 0);}

    inline float GetMass(){return m_Mass;}
    inline Vector2D Position(){return m_Position;}
    inline Vector2D Velocity(){return m_Velocity;}
    inline Vector2D Acceleration(){return m_Acceleration;}

    void Update(float dt){
        m_Acceleration.X = (m_Force.X + m_Friction.X)/m_Mass;
        m_Acceleration.Y = m_Gravity + m_Force.Y/m_Mass;
        m_Velocity = m_Acceleration*dt;
        m_Position = m_Velocity*dt;
    }
};

#endif