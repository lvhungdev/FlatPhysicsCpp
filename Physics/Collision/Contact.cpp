#include <algorithm>
#include "Contact.h"

Contact::~Contact()
{
    delete point1;
    delete point2;
}

void Contact::resolve()
{
    bool isBodyAStatic = bodyA->inverseMass == 0.0f && bodyA->inverseInertia == 0.0f;
    bool isBodyBStatic = bodyB->inverseMass == 0.0f && bodyB->inverseInertia == 0.0f;

    if (isBodyAStatic && isBodyBStatic) return;

    resolvePenetration();
    resolveVelocity();
}

void Contact::resolvePenetration() const
{
    float totalInverseMass = bodyA->inverseMass + bodyB->inverseMass;

    bodyA->position -= normal * penetration * (bodyA->inverseMass / totalInverseMass);
    bodyB->position += normal * penetration * (bodyB->inverseMass / totalInverseMass);

    // TODO Adjust contact points after resolving penetration
}

void Contact::resolveVelocity()
{
    if (point1 == nullptr) return;
    if (point2 == nullptr)
    {
        point2 = point1;
    }

    FlatVector impulseAlongNormal1 = normal * calculateImpulseAtPoint(*point1, normal) * 0.5f;
    FlatVector impulseAlongNormal2 = normal * calculateImpulseAtPoint(*point2, normal) * 0.5f;

    FlatVector normalPerp = normal.getPerpendicular();
    FlatVector friction1 = normalPerp * calculateImpulseAtPoint(*point1, normalPerp) * 0.5f * 0.2f;
    FlatVector friction2 = normalPerp * calculateImpulseAtPoint(*point2, normalPerp) * 0.5f * 0.2f;

    bodyA->applyImpulse((impulseAlongNormal1 + friction1) * -1, *point1);
    bodyA->applyImpulse((impulseAlongNormal2 + friction2) * -1, *point2);

    bodyB->applyImpulse(impulseAlongNormal1 + friction1, *point1);
    bodyB->applyImpulse(impulseAlongNormal2 + friction2, *point2);
}

float Contact::calculateImpulseAtPoint(const FlatVector& point, const FlatVector& contactNormal) const
{
    float restitution = std::min(bodyA->restitution, bodyB->restitution);

    FlatVector rAPerpendicular = (point - bodyA->position).getPerpendicular();
    FlatVector velocityA = bodyA->linearVelocity + rAPerpendicular * bodyA->angularVelocity;

    FlatVector rBPerpendicular = (point - bodyB->position).getPerpendicular();
    FlatVector velocityB = bodyB->linearVelocity + rBPerpendicular * bodyB->angularVelocity;

    FlatVector relativeVelocity = velocityB - velocityA;

    float impulse = -(1 + restitution) * relativeVelocity.dotProduct(contactNormal) /
                    ((bodyA->inverseMass + bodyB->inverseMass) +
                     (rAPerpendicular.dotProduct(contactNormal) * rAPerpendicular.dotProduct(contactNormal) *
                      bodyA->inverseInertia) +
                     (rBPerpendicular.dotProduct(contactNormal) * rBPerpendicular.dotProduct(contactNormal) *
                      bodyB->inverseInertia));

    return impulse;
}
