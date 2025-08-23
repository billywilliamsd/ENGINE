#ifndef TEXT_H
#define TEXT_H
#include <SDL3/SDL.h>
#include <string>
using namespace std;

class Text{
public:
    Text(){
        m_Texture = nullptr;
        m_Width = 0;
        m_Height = 0;
    }
    ~Text(){
        SDL_DestroyTexture(m_Texture);
    }

    bool loadFromRenderedText(string s, SDL_Color c);
    void Render(float x, float y);
    void SetColor(Uint8 r, Uint8 g, Uint8 b){SDL_SetTextureColorMod(m_Texture, r, g, b);}

    SDL_Texture* m_Texture;
    int m_Width;
    int m_Height;
};

class InputText : public Text{
public:
    InputText() : Text(){
        down = false;
        tick = 0;
    }
    
    bool down;
    Uint64 tick;
};

class TextManager{
    TextManager(){}
    static TextManager* instance;
public:
    static TextManager* GetInstance(){return (instance == nullptr) ? new TextManager() : instance;}
    void Update();
};
#endif