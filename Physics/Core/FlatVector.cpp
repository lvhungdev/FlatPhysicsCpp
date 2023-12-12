#include <cmath>
#include "FlatVector.h"

FlatVector::FlatVector() = default;

FlatVector::FlatVector(float x, float y)
{
    this->x = x;
    this->y = y;
}

FlatVector FlatVector::operator+(const FlatVector& other) const
{
    return { x + other.x, y + other.y };
}

FlatVector FlatVector::operator+(const float other) const
{
    return { x + other, y + other };
}

FlatVector FlatVector::operator-(const FlatVector& other) const
{
    return { x - other.x, y - other.y };
}

FlatVector FlatVector::operator-(float other) const
{
    return { x - other, y - other };
}

FlatVector FlatVector::operator*(float other) const
{
    return { x * other, y * other };
}

FlatVector FlatVector::operator/(float other) const
{
    return { x / other, y / other };
}

void FlatVector::operator+=(const FlatVector& other)
{
    this->x += other.x;
    this->y += other.y;
}

void FlatVector::operator+=(float other)
{
    this->x += other;
    this->y += other;
}

void FlatVector::operator-=(const FlatVector& other)
{
    this->x -= other.x;
    this->y -= other.y;
}

void FlatVector::operator-=(float other)
{
    this->x -= other;
    this->y -= other;
}

void FlatVector::operator*=(float other)
{
    this->x *= other;
    this->y *= other;
}

void FlatVector::operator/=(float other)
{
    if (other == 0) return;

    this->x /= other;
    this->y /= other;
}

float FlatVector::dotProduct(const FlatVector& other) const
{
    return this->x * other.x + this->y * other.y;
}

float FlatVector::getLength() const
{
    return sqrtf(this->x * this->x + this->y * this->y);
}

float FlatVector::getLengthSquared() const
{
    return this->x * this->x + this->y * this->y;
}

FlatVector FlatVector::getNormalized() const
{
    if (x == 0.0f && y == 0.0f) return FlatVector(0.0f, 0.0f);

    return *this / getLength();
}

FlatVector FlatVector::getPerpendicular() const
{
    return FlatVector(-y, x);
}

FlatVector FlatVector::getRotated(float angle) const
{
    return FlatVector(
            x * cosf(angle) - y * sinf(angle),
            x * sinf(angle) + y * cosf(angle)
    );
}
