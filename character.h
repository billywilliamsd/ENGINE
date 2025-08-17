#ifndef CHARACTER_H
#define CHARACTER_H
#include "GameObject.h"

class Character : public GameObject{
public:
    Character(Properties* p) : GameObject(p){}

    virtual void Draw() = 0;
    virtual void Clean() = 0;
    virtual void Update(float dt) = 0;

protected:
    string m_Name;
};

#endif