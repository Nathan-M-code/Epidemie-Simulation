#ifndef VIRUS_H_INCLUDED
#define VIRUS_H_INCLUDED

#include "myDrawable.h"

class Virus : public MyDrawable{
public:
    Virus(std::string name);
    Virus(std::string name, float prContagion, float prDeath, unsigned distanceContagion, unsigned dayLeft);
    ~Virus();

    unsigned getDistanceConta();
    float getContagion();
    float getDeath();
    unsigned getDayLeft();

    void setPositionByButtonMove(sf::Vector2i &mousePos);
    void scaleByButtonScale(sf::Vector2i &mousePos);

    bool mouseIsOnConta(sf::Vector2i &mousePos);
    void setArrowDisplayed(bool act);
    bool isArrowDisplayed();
    void setObjectifArrow(sf::Vector2i &pos);

    std::string getName();

    void drawIcon(sf::RenderWindow &window);

private:
    float _contagion;
    float _death;
    unsigned _distanceContagion;
    unsigned _dayLeft;

    std::string _name;

    sf::Sprite _spriteConta;
    bool _arrowDisplayed;
    sf::Vector2i _objArrow;

};

#endif // VIRUS_H_INCLUDED
