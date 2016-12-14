#ifndef __CollisionManager__
#define __CollisionManager__

#include <iostream>
#include <vector>

class Player;
class GameObject;

class CollisionManager
{
public:

    void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);
};

#endif
