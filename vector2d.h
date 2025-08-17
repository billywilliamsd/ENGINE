#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>
using namespace std;

class Vector2D{
    //v3 = v1 + v2

public:
    float X, Y;
    Vector2D(float x = 0, float y = 0):X(x), Y(y){}

    //v3 = v1 + v2
    inline Vector2D operator+(const Vector2D& v2) const{
        return Vector2D(X + v2.X, Y + v2. Y);
    }

    //v3 = v1 - v2
    inline Vector2D operator-(const Vector2D& v2) const{
        return Vector2D(X - v2.X, Y - v2. Y);
    }

    //v1 = v1*scalar
    inline Vector2D operator*(const float scalar) const{
        return Vector2D(X*scalar, Y*scalar);
    }

    void Log(string msg = ""){
        cout << msg << "(X Y) = " << "(" << X << " " << Y << ")" << endl;
    }
};

#endif