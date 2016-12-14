/*** SOURCE CODE ATTRIBUTION
**  Created by shaun mitchell on 17/02/2013.
**  Copyright (c) 2013 shaun mitchell. All rights reserved.
**  I modified some part of the code, not my own full code
***/

#ifndef __StateParser__
#define __StateParser__

#include <iostream>
#include <vector>
#include "tinyxml.h"

class GameObject;

class StateParser
{
public:

    StateParser() {}
    ~StateParser() {}

    bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);

private:

    void parseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*> *pObjects);
    void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs);
};

#endif
