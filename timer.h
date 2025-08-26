#ifndef TIMER_H
#define TIMER_H

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer{
    Timer(){}
    static Timer* instance;
    float m_DeltaTime;
    float m_LastTime;
public:
    inline static Timer* GetInstance(){return (instance == nullptr) ? new Timer() : instance;}
    inline float GetDeltaTime(){return m_DeltaTime;}
    void Tick();
};

#endif