#include "FlatBody.h"

void FlatBody::integrate(float delta)
{
    linearVelocity += linearAcceleration * delta;
    position += linearVelocity * delta;

    rotation += angularVelocity * delta;
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
