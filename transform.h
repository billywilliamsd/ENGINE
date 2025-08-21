#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "vector2d.h"

class Transform{
public:
    inline void TranslateX(float x){X += x;}
    inline void TranslateY(float y){Y += y;}
    inline void Translate(Vector2D v){X += v.X; Y += v.Y;}
    
    float X, Y;

    Transform(float x = 0, float y = 0):X(x), Y(y){}
    void Log(string msg = ""){
        cout << msg << "(X Y) = " << "(" << X << " " << Y << ")" << endl;
    }
};

#endif