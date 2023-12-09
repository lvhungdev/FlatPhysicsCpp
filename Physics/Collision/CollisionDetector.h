#pragma once

#include "Physics/Core/FlatBody.h"
#include "Contact.h"

class CollisionDetector
{
public:
    static bool detect(FlatBody* body1, FlatBody* body2, Contact* outContact);
};
