#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "dataGraphic4u.h"
#include "myDrawable.h"
#include "virus.h"

class Graphic : public MyDrawable{
public:
    Graphic(int x, int y, unsigned width, unsigned height, Virus *virusWanted);
    ~Graphic();

    void addData(DataGraphic4u &data);
    void addData(unsigned healthy, unsigned contaminated, unsigned resistant, unsigned dead);

    void setPositionByButtonMove(sf::Vector2i &mousePos);
    void scaleByButtonScale(sf::Vector2i &mousePos);

    bool mouseIsOnUnlink(sf::Vector2i &mousePos);

    Virus *getVirusWanted();

    void draw(sf::RenderWindow &window);
private:
    sf::RectangleShape _lineX;
    sf::RectangleShape _lineY;

    std::vector<DataGraphic4u> _data;

    Virus *_virusWanted;

    sf::Sprite _spriteUnlink;
};

#endif // GRAPH_H_INCLUDED
