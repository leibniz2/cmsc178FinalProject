/*** SOURCE CODE ATTRIBUTION
**  Created by shaun mitchell on 17/02/2013.
**  Copyright (c) 2013 shaun mitchell. All rights reserved.
**  I modified some part of the code, not my own full code
***/

#ifndef __LevelParser__
#define __LevelParser__

#include <iostream>
#include <vector>
#include "tinyxml.h"

class Level;
struct Tileset;
class Layer;
class TileLayer;

class LevelParser
{
public:

    Level* parseLevel(const char* stateFile);

private:

    void parseTextures(TiXmlElement* pTextureRoot);
    void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
    void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel);
    void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers);

    int m_tileSize;
    int m_width;
    int m_height;
};

#endif /* defined(__SDL_Game_Programming_Book__LevelParser__) */
