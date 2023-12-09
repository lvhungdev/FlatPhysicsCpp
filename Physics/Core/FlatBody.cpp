#include "FlatBody.h"

void FlatBody::integrate(float delta)
{
    linearVelocity += linearAcceleration * delta;
    position += linearVelocity * delta;
}

void FlatBody::applyImpulse(const FlatVector& impulse)
{
    linearVelocity += impulse * inverseMass;
}
