#include <algorithm>
#include "Contact.h"

Contact::~Contact()
{
    delete point1;
    delete point2;
}

void Contact::resolve()
{
    // TODO Add inverseInertia check when rotation is implemented
    if (bodyA->inverseMass == 0.0f && bodyB->inverseMass == 0.0f)
    {
        return;
    }

    resolvePenetration();
    resolveVelocity();
}

void Contact::resolvePenetration() const
{
    float totalInverseMass = bodyA->inverseMass + bodyB->inverseMass;

    bodyA->position -= normal * penetration * (bodyA->inverseMass / totalInverseMass);
    bodyB->position += normal * penetration * (bodyB->inverseMass / totalInverseMass);
}

void Contact::resolveVelocity() const
{
    float restitution = std::min(bodyA->restitution, bodyB->restitution);
    FlatVector relativeVelocity = bodyB->linearVelocity - bodyA->linearVelocity;

    float impulseAlongNormal = -(1 + restitution) * relativeVelocity.dotProduct(normal) /
                               (bodyA->inverseMass + bodyB->inverseMass);

    FlatVector impulse = normal * impulseAlongNormal;

    bodyA->applyImpulse(impulse * -1);
    bodyB->applyImpulse(impulse);
}
