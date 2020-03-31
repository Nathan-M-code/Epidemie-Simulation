#ifndef MYDRAWABLE_H_INCLUDED
#define MYDRAWABLE_H_INCLUDED

#include "TextureLoader.h"

class MyDrawable{
public:
    MyDrawable(int x, int y, unsigned width, unsigned height, unsigned widthMin, unsigned heightMin);
    ~MyDrawable();

    bool mouseIsOnMove(sf::Vector2i &mousePos);
    bool mouseIsOnScale(sf::Vector2i &mousePos);
    bool mouseIsOnDelete(sf::Vector2i &mousePos);

    bool mouseIsOn(sf::Vector2i &mousePos);

    virtual void setPositionByButtonMove(sf::Vector2i &mousePos);
    virtual void scaleByButtonScale(sf::Vector2i &mousePos);
    virtual void saveOldCoo();
    virtual void tpAllPersonIn();

protected:
    unsigned _width;
    unsigned _widthMin;
    unsigned _height;
    unsigned _heightMin;
    int _x;
    int _y;

    sf::Font *_font;

    sf::Sprite _spriteMove;
    sf::Sprite _spriteScale;
    sf::Sprite _spriteDelete;
};

#endif // MYDRAWABLE_H_INCLUDED
