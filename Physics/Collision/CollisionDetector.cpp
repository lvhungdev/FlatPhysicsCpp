#include "CollisionDetector.h"

bool circleVsCircle(FlatVector& circleACenter, float circleARadius, FlatVector& circleBCenter, float circleBRadius,
        Contact* outContact);

bool CollisionDetector::detect(FlatBody* bodyA, FlatBody* bodyB, Contact* outContact)
{
    if (outContact != nullptr)
    {
        outContact->bodyA = bodyA;
        outContact->bodyB = bodyB;
    }

    return circleVsCircle(bodyA->position, bodyA->flatShape.radius, bodyB->position, bodyB->flatShape.radius,
            outContact);
}

bool circleVsCircle(FlatVector& circleACenter, float circleARadius, FlatVector& circleBCenter, float circleBRadius,
        Contact* outContact)
{
    float distance = (circleBCenter - circleACenter).getLength();
    float penetration = circleARadius + circleBRadius - distance;

    if (penetration < 0.0f) return false;

    if (outContact == nullptr) return true;

    outContact->penetration = penetration;
    outContact->normal = (circleBCenter - circleACenter).getNormalized();
    outContact->point1 = new FlatVector(circleACenter + outContact->normal * circleARadius);

    return true;
}
