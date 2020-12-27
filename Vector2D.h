// #pragma once
#ifndef _VECTOR2D_H
#define _VECTOR2D_H
#include <iostream>
using namespace std;

class Vector2D
{
public:
    double x;
    double y;

    Vector2D();
    Vector2D(double x, double y);

    Vector2D &Substract(const Vector2D &vec);
    Vector2D &Multiply(const Vector2D &vec);
    Vector2D &Divide(const Vector2D &vec);
    Vector2D &Add(const Vector2D &vec);

    friend Vector2D &operator+(Vector2D &v1, const Vector2D &v2);
    friend Vector2D &operator-(Vector2D &v1, const Vector2D &v2);
    friend Vector2D &operator*(Vector2D &v1, const Vector2D &v2);
    friend Vector2D &operator/(Vector2D &v1, const Vector2D &v2);

    Vector2D &operator+=(const Vector2D &vec);
    Vector2D &operator-=(const Vector2D &vec);
    Vector2D &operator*=(const Vector2D &vec);
    Vector2D &operator/=(const Vector2D &vec);

    Vector2D &operator*(const int &i);
    Vector2D &Zero();

    friend ostream &operator<<(ostream &stream, const Vector2D &vec);

    bool &operator==(const Vector2D &vec);
};
#endif