#include "timer.h"
#include <iostream>
#include "texturemanager.h"
#include <SDL3/SDL.h>
using namespace std;

Timer* Timer::instance = nullptr;

void Timer::Tick(){
    Uint64 frametime = SDL_GetTicksNS() - m_LastTime;
    m_DeltaTime = frametime * (TARGET_FPS/1000000000.0f);

    Uint64 sleepframe = (1000000000.0f / 60) - frametime;
    SDL_DelayPrecise(sleepframe);
    double A = sleepframe + frametime;
    double B = 1000000000.0f / A;
    string FPS = "FPS: ";
    FPS.append(to_string(B));
    TextureManager::GetInstance()->LoadText("FPS", FPS, {0x00, 0x00, 0x00, 0x00});

    if(m_DeltaTime > TARGET_DELTATIME)
        m_DeltaTime = TARGET_DELTATIME;
    
    m_LastTime = SDL_GetTicksNS();
}