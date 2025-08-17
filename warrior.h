#ifndef WARRIOR_H
#define WARRIOR_H
#include "character.h"
#include "animation.h"

class Warrior : public Character{
public:
    Warrior(Properties* p);

    virtual void Draw();
    virtual void Clean();
    virtual void Update(float dt);

private:
    Animation* m_Animation;
};

#endif 