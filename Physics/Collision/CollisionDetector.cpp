#include <limits>
#include "Utils/MathUtils.h"
#include "CollisionDetector.h"

bool circleVsCircle(FlatVector& circleACenter, float circleARadius, FlatVector& circleBCenter, float circleBRadius,
        Contact* outContact);

bool polygonVsPolygon(FlatVector* verticesA, int vertexCountA, FlatVector* verticesB, int vertexCountB,
        Contact* outContact);

bool polygonVsPolygon(FlatVector* verticesA, int vertexCountA,
        FlatVector* verticesB, int vertexCountB, FlatVector* outNormal, float* outPenetration,
        FlatVector** outContactPoint1, FlatVector** outContactPoint2);

void findContactPointsPolygonPolygon(const FlatVector& startEdge, const FlatVector& endEdge,
        FlatVector* verticesB, int verticesBLength, const FlatVector& normal, float penetration,
        FlatVector** outContactPoint1, FlatVector** outContactPoint2);

bool CollisionDetector::detect(FlatBody* bodyA, FlatBody* bodyB, Contact* outContact)
{
    if (outContact != nullptr)
    {
        outContact->bodyA = bodyA;
        outContact->bodyB = bodyB;
    }

    if (bodyA->shape.type == FlatShapeType::Circle && bodyB->shape.type == FlatShapeType::Circle)
    {
        return circleVsCircle(bodyA->position, bodyA->shape.radius, bodyB->position, bodyB->shape.radius,
                outContact);
    } else if (bodyA->shape.type == FlatShapeType::Polygon && bodyB->shape.type == FlatShapeType::Polygon)
    {
        return polygonVsPolygon(bodyA->vertices, bodyA->vertexCount, bodyB->vertices, bodyB->vertexCount,
                outContact);
    }

    return false;
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


bool polygonVsPolygon(FlatVector* verticesA, int vertexCountA, FlatVector* verticesB, int vertexCountB,
        Contact* outContact)
{
    float penetrationA;
    FlatVector normalA;
    FlatVector* contactPointA1 = nullptr;
    FlatVector* contactPointA2 = nullptr;

    float penetrationB;
    FlatVector normalB;
    FlatVector* contactPointB1 = nullptr;
    FlatVector* contactPointB2 = nullptr;

    bool isCollidedA = polygonVsPolygon(verticesA, vertexCountA, verticesB, vertexCountB, &normalA, &penetrationA,
            &contactPointA1, &contactPointA2);
    if (!isCollidedA) return false;

    bool isCollidedB = polygonVsPolygon(verticesB, vertexCountB, verticesA, vertexCountA, &normalB, &penetrationB,
            &contactPointB1, &contactPointB2);
    if (!isCollidedB) return false;

    if (outContact == nullptr) return true;

    if (MathUtils::nearlyEqual(penetrationA, penetrationB))
    {
        outContact->penetration = penetrationA;
        outContact->normal = normalA;

        if (contactPointA1 == nullptr)
        {
            outContact->point1 = contactPointB1;
            outContact->point2 = contactPointB2;
        } else if (contactPointB1 == nullptr)
        {
            outContact->point1 = contactPointA1;
            outContact->point2 = contactPointA2;
        } else
        {
            outContact->point1 = contactPointA1;
            outContact->point2 = contactPointB1;
        }
    } else if (penetrationA < penetrationB)
    {
        outContact->penetration = penetrationA;
        outContact->normal = normalA;
        outContact->point1 = contactPointA1;
        outContact->point2 = contactPointA2;
    } else
    {
        outContact->penetration = penetrationB;
        outContact->normal = normalB * -1;
        outContact->point1 = contactPointB1;
        outContact->point2 = contactPointB2;
    }

    return true;
}

bool polygonVsPolygon(FlatVector* verticesA, int vertexCountA,
        FlatVector* verticesB, int vertexCountB, FlatVector* outNormal, float* outPenetration,
        FlatVector** outContactPoint1, FlatVector** outContactPoint2)
{
    float penetration = std::numeric_limits<float>::max();
    FlatVector normal;
    FlatVector startEdge;
    FlatVector endEdge;

    for (int i = 0; i < vertexCountA; i++)
    {
        float maxPenetration = -std::numeric_limits<float>::max();
        FlatVector tmpNormal;

        FlatVector tmpStartEdge = verticesA[(i + 1) % vertexCountA];
        FlatVector tmpEndEdge = verticesA[i];
        FlatVector axis = (tmpStartEdge - tmpEndEdge).getPerpendicular().getNormalized();

        for (int j = 0; j < vertexCountB; j++)
        {
            float tmpPenetration = (verticesA[i] - verticesB[j]).dotProduct(axis);

            if (tmpPenetration > maxPenetration)
            {
                maxPenetration = tmpPenetration;
                tmpNormal = axis;
            }
        }

        if (maxPenetration < 0) return false;

        if (maxPenetration < penetration)
        {
            penetration = maxPenetration;
            normal = tmpNormal;
            startEdge = tmpStartEdge;
            endEdge = tmpEndEdge;
        }
    }

    findContactPointsPolygonPolygon(startEdge, endEdge, verticesB, vertexCountB,
            normal, penetration, outContactPoint1, outContactPoint2);

    if (outNormal != nullptr) *outNormal = normal;
    if (outPenetration != nullptr) *outPenetration = penetration;

    return true;
}

void findContactPointsPolygonPolygon(const FlatVector& startEdge, const FlatVector& endEdge,
        FlatVector* verticesB, int verticesBLength, const FlatVector& normal, float penetration,
        FlatVector** outContactPoint1, FlatVector** outContactPoint2)
{
    if (outContactPoint1 == nullptr || outContactPoint2 == nullptr) return;

    FlatVector edge = endEdge - startEdge;
    FlatVector toMove = normal * penetration;

    for (int i = 0; i < verticesBLength; i++)
    {
        if ((verticesB[i] - startEdge).dotProduct(edge) < 0) continue;
        if ((verticesB[i] - endEdge).dotProduct(edge * -1) < 0) continue;

        FlatVector line = verticesB[i] - startEdge + toMove;
        float dot = line.dotProduct(edge);

        if (MathUtils::nearlyEqual(line.getLengthSquared(), dot * dot / edge.getLengthSquared()))
        {
            if (*outContactPoint1 == nullptr)
            {
                *outContactPoint1 = &verticesB[i];
            } else
            {
                *outContactPoint2 = &verticesB[i];
            }
        }
    }
}
