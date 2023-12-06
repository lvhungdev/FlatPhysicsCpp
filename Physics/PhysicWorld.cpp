#include "PhysicWorld.h"

PhysicWorld::~PhysicWorld()
{
    for (FlatBody* body : bodies)
    {
        delete body;
    }
}

void PhysicWorld::integrate(float delta)
{
    float localDelta = delta / (float)integrationSteps;

    for (int i = 0; i < integrationSteps; i++)
    {
        for (auto& body : bodies)
        {
            body->integrate(localDelta);
        }
    }
}

void PhysicWorld::addBody(FlatBody* body)
{
    if (body != nullptr)
    {
        bodies.push_back(body);
    }
}

std::vector<FlatBody*> PhysicWorld::getBodies() const
{
    return bodies;
}
