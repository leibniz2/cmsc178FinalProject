#ifndef __GameState__
#define __GameState__

#include <string>
#include <vector>

class GameState
{
public:

    virtual ~GameState() {}

    virtual void update() = 0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual void resume() {}

    virtual std::string getStateID() const = 0;

protected:

    GameState() : m_loadingComplete(false), m_exiting(false)
    {

    }
    
    bool m_loadingComplete;
    bool m_exiting;

    std::vector<std::string> m_textureIDList;
};

#endif
