#include "virus.h"

using namespace std;

Virus::Virus(std::string name) : MyDrawable(0,100,150,100,150,100){
    _contagion = 0.9;
    _death = 0.02;
    _distanceContagion = 10; //px
    _dayLeft = 840; //60 = 1sec

    _name = name;

    _spriteConta.setTexture(*TextureLoader::getTextureConta());
    _spriteConta.setPosition(_x,_y+_height-_spriteConta.getLocalBounds().height);

    _arrowDisplayed = false;
}

Virus::Virus(std::string name, float prContagion, float prDeath, unsigned distanceContagion, unsigned dayLeft): MyDrawable(0,100,150,100,150,100){
    _contagion = prContagion;
    _death = prDeath;
    _distanceContagion = distanceContagion; //px
    _dayLeft = dayLeft; //60 = 1sec

    _name = name;

    _spriteConta.setTexture(*TextureLoader::getTextureConta());
    _spriteConta.setPosition(_x,_y+_height-_spriteConta.getLocalBounds().height);

    _arrowDisplayed = false;
}


Virus::~Virus(){

}

void Virus::setPositionByButtonMove(sf::Vector2i &mousePos){
    MyDrawable::setPositionByButtonMove(mousePos);

    _spriteConta.setPosition(_x,_y+_height-_spriteConta.getLocalBounds().height);
}
void Virus::scaleByButtonScale(sf::Vector2i &mousePos){
    MyDrawable::scaleByButtonScale(mousePos);

    _spriteConta.setPosition(_x,_y+_height-_spriteConta.getLocalBounds().height);
}

unsigned Virus::getDistanceConta(){
    return _distanceContagion;
}

float Virus::getContagion(){
    return _contagion;
}
float Virus::getDeath(){
    return _death;
}
unsigned Virus::getDayLeft(){
    return _dayLeft;
}
std::string Virus::getName(){
    return _name;
}

bool Virus::mouseIsOnConta(sf::Vector2i &mousePos){
    if(mousePos.x >= _x && mousePos.x <= _x+_spriteConta.getLocalBounds().width){
        if(mousePos.y >= _spriteConta.getPosition().y && mousePos.y <= _y+_height){
            return true;
        }
    }
    return false;
}

void Virus::setArrowDisplayed(bool act){
    _arrowDisplayed = act;
}
bool Virus::isArrowDisplayed(){
    return _arrowDisplayed;
}
void Virus::setObjectifArrow(sf::Vector2i &pos){
    _objArrow = pos;
}

void Virus::drawIcon(sf::RenderWindow &window){
    sf::Text textName;
    textName.setFont(*_font);
    textName.setCharacterSize(16);
    textName.setString(_name);
    textName.setPosition(_x+(_width/2)-(textName.getLocalBounds().width/2),_y+(_height/2)-(textName.getLocalBounds().height/2));

    sf::RectangleShape rs;
    rs.setFillColor(sf::Color(100,100,100,150));
    rs.setOutlineThickness(1);
    rs.setPosition(_x,_y);
    rs.setSize(sf::Vector2f(_width,_height));

    window.draw(rs);
    window.draw(textName);

    window.draw(_spriteMove);
    window.draw(_spriteScale);
    window.draw(_spriteDelete);
    window.draw(_spriteConta);

    if(_arrowDisplayed){
        sf::Vertex line[] ={sf::Vertex(sf::Vector2f(_spriteConta.getPosition().x, _spriteConta.getPosition().y)),sf::Vertex(sf::Vector2f(_objArrow.x, _objArrow.y))};
        window.draw(line, 2, sf::Lines);
    }
}
