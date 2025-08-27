#include "timer.h"
#include <iostream>
#include <SDL3/SDL.h>
using namespace std;

Timer* Timer::instance = nullptr;

void Timer::Tick(){
    m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (TARGET_FPS/1000.0f);

    if(m_DeltaTime > TARGET_DELTATIME)
        m_DeltaTime = TARGET_DELTATIME;

    cout << m_DeltaTime << endl;
    m_LastTime = SDL_GetTicks();
}