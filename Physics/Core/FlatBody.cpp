#include "FlatBody.h"

FlatBody::FlatBody(const FlatShape& shape, const FlatVector& position)
{
    this->shape = shape;

    this->vertices = new FlatVector[shape.vertexCount];
    this->vertexCount = shape.vertexCount;

    this->position = position;

    this->updateVertices();
}

FlatBody::~FlatBody()
{
    delete[] vertices;
}

void FlatBody::integrate(float delta)
{
    linearVelocity += linearAcceleration * delta;
    position += linearVelocity * delta;

    rotation += angularVelocity * delta;

    updateVertices();
}

void FlatBody::applyImpulse(const FlatVector& impulse)
{
    linearVelocity += impulse * inverseMass;
}

void FlatBody::applyImpulse(const FlatVector& impulse, const FlatVector& contactPoint)
{
    linearVelocity += impulse * inverseMass;
    angularVelocity += (contactPoint - position).getPerpendicular().dotProduct(impulse) * inverseInertia;
}

void FlatBody::updateVertices() const
{
    for (int i = 0; i < shape.vertexCount; i++)
    {
        vertices[i] = shape.vertices[i].getRotated(rotation) + position;
    }
}
