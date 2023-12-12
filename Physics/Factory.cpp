#include "Factory.h"

FlatBody* Factory::createCircleBody(const FlatVector& position, float radius)
{
    FlatShape shape = FlatShape();
    shape.type = FlatShapeType::Circle;
    shape.radius = radius;

    FlatBody* body = new FlatBody(shape, position);

    return body;
}

FlatBody* Factory::createBoxBody(const FlatVector& position, float width, float height)
{
    FlatShape shape = FlatShape();
    shape.type = FlatShapeType::Polygon;
    shape.vertexCount = 4;
    shape.vertices = new FlatVector[shape.vertexCount];

    shape.vertices[0] = FlatVector(-width / 2, height / 2);
    shape.vertices[1] = FlatVector(width / 2, height / 2);
    shape.vertices[2] = FlatVector(width / 2, -height / 2);
    shape.vertices[3] = FlatVector(-width / 2, -height / 2);

    FlatBody* body = new FlatBody(shape, position);

    return body;
}

FlatBody* Factory::createStaticBoxBody(const FlatVector& position, float width, float height)
{
    FlatBody* body = createBoxBody(position, width, height);
    body->inverseMass = 0.0f;
    body->inverseInertia = 0.0f;

    return body;
}
