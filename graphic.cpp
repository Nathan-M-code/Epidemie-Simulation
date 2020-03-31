#include "graphic.h"

using namespace std;

Graphic::Graphic(int x, int y, unsigned width, unsigned height, Virus *virusWanted) : MyDrawable(x,y,width,height,150,100){
    _lineX.setSize(sf::Vector2f(_width,1));
    _lineX.setPosition(_x,_y+_height);
    _lineY.setSize(sf::Vector2f(1,_height));
    _lineY.setPosition(_x,_y);

    _virusWanted = virusWanted;

    sf::Texture *texture = TextureLoader::getTextureUnlink();
    sf::Vector2u size = texture->getSize();
    _spriteUnlink.setTexture(*texture);
    _spriteUnlink.setPosition(_x,_y+_height-size.y);
}
Graphic::~Graphic(){}

void Graphic::addData(DataGraphic4u &data){
    _data.push_back(data);
}
void Graphic::addData(unsigned healthy, unsigned contaminated, unsigned resistant, unsigned dead){
    _data.push_back(DataGraphic4u(healthy,contaminated,resistant,dead));
}

bool Graphic::mouseIsOnUnlink(sf::Vector2i &mousePos){
    if(mousePos.x >= _x && mousePos.x <= _x+_spriteUnlink.getTextureRect().width){
        if(mousePos.y >= _spriteUnlink.getPosition().y && mousePos.y <= _spriteUnlink.getPosition().y+_spriteUnlink.getTextureRect().height){
            return true;
        }
    }
    return false;
}

void Graphic::scaleByButtonScale(sf::Vector2i &mousePos){
    MyDrawable::scaleByButtonScale(mousePos);

    _lineX.setSize(sf::Vector2f(_width,1));
    _lineY.setSize(sf::Vector2f(1,_height));
    _lineX.setPosition(_x,_y+_height);

    sf::Vector2u size = _spriteUnlink.getTexture()->getSize();
    _spriteUnlink.setPosition(_x,_y+_height-size.y);
}

void Graphic::setPositionByButtonMove(sf::Vector2i &mousePos){
    MyDrawable::setPositionByButtonMove(mousePos);

    _lineX.setPosition(_x,_y+_height);
    _lineY.setPosition(_x,_y);

    sf::Vector2u size = _spriteUnlink.getTexture()->getSize();
    _spriteUnlink.setPosition(_x,_y+_height-size.y);
}

Virus* Graphic::getVirusWanted(){
    return _virusWanted;
}

void Graphic::draw(sf::RenderWindow &window){
    float lineWidth = (float)_width/_data.size();
    //cout << lineWidth << endl;

    for(unsigned i=0;i<_data.size();i++){
        unsigned nbTot = _data[i].getNbTot();
        //cout << nbTot << endl;
        float percent;
        float lineHeigth;
        //--------------------------
        sf::RectangleShape lineDead;
        lineDead.setPosition(_x+i*lineWidth, _y);
        percent = (float)_data[i].dead/nbTot;
        lineHeigth = _height*percent;
        //cout << lineHeigth;
        lineDead.setSize(sf::Vector2f(lineWidth, lineHeigth));
        lineDead.setFillColor(sf::Color(100,100,100));
        //--------------------------
        sf::RectangleShape lineResistant;
        lineResistant.setPosition(_x+i*lineWidth, lineDead.getPosition().y+lineDead.getSize().y);
        percent = (float)_data[i].resistant/nbTot;
        lineHeigth = _height*percent;
        //cout<<" "<<lineHeigth;
        lineResistant.setSize(sf::Vector2f(lineWidth, lineHeigth));
        lineResistant.setFillColor(sf::Color::Green);
        //--------------------------
        sf::RectangleShape lineHealthy;
        lineHealthy.setPosition(_x+i*lineWidth, lineResistant.getPosition().y+lineResistant.getSize().y);
        percent = (float)_data[i].healthy/nbTot;
        lineHeigth = _height*percent;
        //cout<<lineHeigth<<endl;
        lineHealthy.setSize(sf::Vector2f(lineWidth, lineHeigth));
        lineHealthy.setFillColor(sf::Color::Blue);
        //--------------------------
        sf::RectangleShape lineContaminated;
        lineContaminated.setPosition(_x+i*lineWidth, lineHealthy.getPosition().y+lineHealthy.getSize().y);
        percent = (float)_data[i].contaminated/nbTot;
        lineHeigth = _height*percent;
        //cout<<" "<<lineHeigth<<endl;
        lineContaminated.setSize(sf::Vector2f(lineWidth, lineHeigth));
        lineContaminated.setFillColor(sf::Color::Red);

        window.draw(lineDead);
        window.draw(lineResistant);
        window.draw(lineHealthy);
        window.draw(lineContaminated);
    }

    window.draw(_lineX);
    window.draw(_lineY);

    window.draw(_spriteMove);
    window.draw(_spriteScale);
    window.draw(_spriteDelete);
    window.draw(_spriteUnlink);

    sf::Text virusName;
    virusName.setFont(*_font);
    virusName.setCharacterSize(16);
    if(_virusWanted == nullptr)
        virusName.setString("General");
    else
        virusName.setString(_virusWanted->getName());
    virusName.setPosition(_x+(_width/2)-virusName.getLocalBounds().width/2,_y+_height+5);

    window.draw(virusName);
}
