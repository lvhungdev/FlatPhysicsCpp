#include "PhysicWorld.h"
#include "Collision/Contact.h"
#include "Collision/CollisionDetector.h"

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

    for (int step = 0; step < integrationSteps; step++)
    {
        for (auto& body : bodies)
        {
            body->integrate(localDelta);
        }

        for (int i = 0; i < bodies.size(); i++) {
            for (int j = i + 1; j < bodies.size(); j++) {
                Contact contact;
                bool isCollided = CollisionDetector::detect(bodies[i], bodies[j], &contact);

                if (isCollided) {
                    contact.resolve();
                }
            }
        }
    }
}

void PhysicWorld::addBody(FlatBody* body)
{
    if (body != nullptr)
    {
        body->linearAcceleration += gravity;
        bodies.push_back(body);
    }
}
