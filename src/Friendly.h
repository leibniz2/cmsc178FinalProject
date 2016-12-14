#ifndef __Friendly__
#define __Friendly__

#include <iostream>
#include "PlatformerObject.h"

// Enemy base class
class Friendly : public PlatformerObject
{
public:

    virtual std::string type() { return "Friend"; }

protected:

    Friendly() : PlatformerObject() {}
    virtual ~Friendly() {}
};

#endif
