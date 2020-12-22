#include "Vector2D.h"


<<<<<<< HEAD
Vector2D::Vector2D() {
=======
Vector2D::Vector2D() 
{
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
    x = 0.0;
    y = 0.0;
}


<<<<<<< HEAD
Vector2D::Vector2D(double x, double y) {
=======
Vector2D::Vector2D(double x, double y) 
{
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
    this->x = x;
    this->y = y;
}

<<<<<<< HEAD
Vector2D& Vector2D::Add(const Vector2D& vec) {
=======
Vector2D& Vector2D::Add(const Vector2D& vec) 
{
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
    this->x += vec.x;
    this->y += vec.y;

    return *this;
}

<<<<<<< HEAD
Vector2D& Vector2D::Substract(const Vector2D& vec) {
=======
Vector2D& Vector2D::Substract(const Vector2D& vec) 
{
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
    this->x -= vec.x;
    this->y -= vec.y;

    return *this;
}

<<<<<<< HEAD
Vector2D& Vector2D::Divide(const Vector2D& vec) {
=======
Vector2D& Vector2D::Divide(const Vector2D& vec) 
{
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
    this->x /= vec.x;
    this->y /= vec.y;

    return *this;
}

<<<<<<< HEAD
Vector2D& Vector2D::Multiply(const Vector2D& vec) {
=======
Vector2D& Vector2D::Multiply(const Vector2D& vec) 
{
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
    this->x *= vec.x;
    this->y *= vec.y;

    return *this;
}

<<<<<<< HEAD
Vector2D& operator+(Vector2D& v1, const Vector2D& v2) {
    return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2) {
    return v1.Substract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2) {
    return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2) {
    return v1.Divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec) {
    return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec) {
    return this->Substract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec) {
    return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec) {
    return this->Divide(vec);
}

ostream& operator<<(ostream& stream, const Vector2D& vec) {
=======
Vector2D& operator+(Vector2D& v1, const Vector2D& v2) 
{
    return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2) 
{
    return v1.Substract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2) 
{
    return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2) 
{
    return v1.Divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec) 
{
    return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec) 
{
    return this->Substract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec) 
{
    return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec) 
{
    return this->Divide(vec);
}

ostream& operator<<(ostream& stream, const Vector2D& vec) 
{
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
    stream << "(" << vec.x << ", " << vec.y << ")";
    return stream;
}

<<<<<<< HEAD
Vector2D& Vector2D::operator*(const int& i) {
=======
Vector2D& Vector2D::operator*(const int& i) 
{
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
    this->x *= i;
    this->y *= i;

    return *this;
}

<<<<<<< HEAD
Vector2D& Vector2D::Zero() {
=======
Vector2D& Vector2D::Zero() 
{
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
    this->x = 0;
    this->y = 0;

    return *this;
}
 