#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "myDrawable.h"
#include "Cursor.h"
#include "CursorFloat.h"
#include "virus.h"
#include "community.h"
#include "TextBox.h"

class Menu : public MyDrawable{
public:
    Menu(int x, int y, unsigned width, unsigned height);
    ~Menu();

    void setPositionByButtonMove(sf::Vector2i &mousePos);
    void scaleByButtonScale(sf::Vector2i &mousePos);

    bool mouseIsOnNewVirus(sf::Vector2i &mousePos);
    bool mouseIsOnNewCommu(sf::Vector2i &mousePos);

    void clickNonButton(bool pressed, sf::Vector2i &mousePos);
    void handlerMouseMotion(sf::Vector2i &mousePos);

    Virus* getNewVirus();
    Community* getNewCommunity();

    void writeKey(sf::Uint32 &key);

    void draw(sf::RenderWindow &window);
private:
    sf::RectangleShape _rsBackground;
    sf::Text _text;

    sf::RectangleShape _rsNewVirus;
    sf::RectangleShape _rsNewCommu;

    std::vector<Cursor *> _listCursor;
    TextBox *_tb;
    CursorFloat *_cursorFloat;
};

#endif // MENU_H_INCLUDED
