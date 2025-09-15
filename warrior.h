#ifndef WARRIOR_H
#define WARRIOR_H
#include "character.h"
#include "animation.h"
#include "Collider.h"
#include "vector2d.h"
#include "RigidBody.h"

class Warrior : public Character{
public:
    Warrior(Properties* p);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(float dt);

    bool idle;
    int orient; //1 down, 2 left, 3 right, 4 up
private:
    Animation* m_Animation;
    RigidBody* m_RigidBody;
    Collider* m_Collider;
    Vector2D m_LastSafePosition;
};

#endif 