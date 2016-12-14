#ifndef __Coin__
#define __Coin__

#include "Friendly.h"
#include "GameObjectFactory.h"
#include "Camera.h"
#include "TileLayer.h"
#include <iostream>

class Coin : public Friendly
{
public:

    Coin() : Friendly()
    {
        moveLeft = true;
    }

    virtual void update()
    {
        m_velocity.m_x = 0;
        m_velocity.m_y = 0;
        // handleAnimation();
    }

    virtual void load(std::unique_ptr<LoaderParams> const &pParams)
    {
        PlatformerObject::load(std::move(pParams));
    }

    virtual void draw()
    {
        if(m_flipped)
        {
            TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX() -  TheCamera::Instance()->getPosition().m_x, (Uint32)m_position.getY() -  TheCamera::Instance()->getPosition().m_y,
                                                  m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha, SDL_FLIP_HORIZONTAL);
        }
        else
        {
            TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX() -  TheCamera::Instance()->getPosition().m_x, (Uint32)m_position.getY() -  TheCamera::Instance()->getPosition().m_y,
                                                  m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha);
        }
    }

private:

    void handleMovement(Vector2D velocity)
    {
        Vector2D newPos = m_position;
        newPos.m_x  = m_position.m_x + velocity.m_x;

        if(!checkCollideTile(newPos))
        {
            m_position.m_x = newPos.m_x;
        }
        else
        {
            if(moveLeft)
            {
                moveLeft = false;
                moveRight = true;
            }
            else if(moveRight)
            {
                moveLeft = true;
                moveRight = false;
            }
        }

        newPos = m_position;
        newPos.m_y += velocity.m_y;

        if(!checkCollideTile(newPos))
        {
            if(m_velocity.m_y == 0)
            {
                if(moveLeft)
                {
                    moveLeft = false;
                    moveRight = true;
                }
                else if(moveRight)
                {
                    moveLeft = true;
                    moveRight = false;
                }
            }

            m_position.m_y = newPos.m_y;
        }
        else
        {
            m_velocity.m_y = 0;
        }
    }

    void handleAnimation()
    {

        if(m_velocity.getX() < 0)
        {
            m_flipped = true;
        }
        else if(m_velocity.getX() > 0)
        {
            m_flipped = false;
        }
        else
        {
            m_currentRow = 0;
            m_numFrames = 1;
        }

        m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
    }

    bool moveLeft;
    bool moveRight;
    bool m_flipped;

};

class CoinCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Coin();
    }
};


#endif
