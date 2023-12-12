#pragma once

#include "Physics/Core/FlatBody.h"
#include "Contact.h"

class CollisionDetector
{
public:
    static bool detect(FlatBody* bodyA, FlatBody* bodyB, Contact* outContact);
};
