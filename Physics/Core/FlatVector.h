#pragma once

class FlatVector
{
public:
    FlatVector();

    FlatVector(float x, float y);

    float x = 0.0f;
    float y = 0.0f;

    FlatVector operator+(const FlatVector& other) const;

    FlatVector operator+(float other) const;

    FlatVector operator-(const FlatVector& other) const;

    FlatVector operator-(float other) const;

    FlatVector operator*(float other) const;

    FlatVector operator/(float other) const;

    void operator+=(const FlatVector& other);

    void operator+=(float other);

    void operator-=(const FlatVector& other);

    void operator-=(float other);

    void operator*=(float other);

    void operator/=(float other);

    float dotProduct(const FlatVector& other) const;

    float getLength() const;

    float getLengthSquared() const;

    FlatVector getNormalized() const;

    FlatVector getPerpendicular() const;

    FlatVector getRotated(float angle) const;
};
