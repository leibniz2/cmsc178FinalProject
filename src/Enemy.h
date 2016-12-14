#ifndef __Enemy__
#define __Enemy__

#include <iostream>
#include "PlatformerObject.h"

// Enemy base class
class Enemy : public PlatformerObject
{
public:

    virtual std::string type() { return "Enemy"; }

protected:

    int m_health;

    Enemy() : PlatformerObject() {}
    virtual ~Enemy() {}
};

#endif
