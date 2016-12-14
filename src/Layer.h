#ifndef __Layer__
#define __Layer__

class Level;

class Layer
{
public:

    virtual ~Layer() {}

    virtual void render() = 0;
    virtual void update(Level* pLevel) = 0;
};


#endif
