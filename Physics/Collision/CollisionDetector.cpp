#include "CollisionDetector.h"

bool circleVsCircle(FlatVector& circle1Center, float circle1Radius, FlatVector& circle2Center, float circle2Radius,
        Contact* outContact);

bool CollisionDetector::detect(FlatBody* body1, FlatBody* body2, Contact* outContact)
{
    if (outContact != nullptr)
    {
        outContact->bodyA = body1;
        outContact->bodyB = body2;
    }

    return circleVsCircle(body1->position, body1->flatShape.radius, body2->position, body2->flatShape.radius,
            outContact);
}

bool circleVsCircle(FlatVector& circle1Center, float circle1Radius, FlatVector& circle2Center, float circle2Radius,
        Contact* outContact)
{
    float distance = (circle2Center - circle1Center).getLength();
    float penetration = circle1Radius + circle2Radius - distance;

    if (penetration < 0.0f) return false;

    if (outContact == nullptr) return true;

    outContact->penetration = penetration;
    outContact->normal = (circle2Center - circle1Center).getNormalized();
    outContact->point1 = new FlatVector(circle1Center + outContact->normal * circle1Radius);
    outContact->point2 = new FlatVector(circle2Center - outContact->normal * circle2Radius);

    return true;
}
