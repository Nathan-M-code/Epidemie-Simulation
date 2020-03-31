#include "myDrawable.h"

MyDrawable::MyDrawable(int x, int y, unsigned width, unsigned height, unsigned widthMin, unsigned heightMin){
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _heightMin = heightMin;
    _widthMin = widthMin;

    _font = TextureLoader::getFont();

    _spriteMove.setTexture(*TextureLoader::getTextureMove());
    _spriteMove.setPosition(_x,_y);

    sf::Texture *texture = TextureLoader::getTextureScale();
    sf::Vector2u size = texture->getSize();
    _spriteScale.setTexture(*texture);
    _spriteScale.setPosition(_x+_width-size.x,_y+_height-size.y);

    texture = TextureLoader::getTextureDelete();
    size = texture->getSize();
    _spriteDelete.setTexture(*texture);
    _spriteDelete.setPosition(_x+_width-size.x,_y);
}
MyDrawable::~MyDrawable(){}

bool MyDrawable::mouseIsOnMove(sf::Vector2i &mousePos){
    if(mousePos.x >= _spriteMove.getPosition().x && mousePos.x <= _spriteMove.getPosition().x+_spriteMove.getTextureRect().width){
        if(mousePos.y >= _spriteMove.getPosition().y && mousePos.y <= _spriteMove.getPosition().y+_spriteMove.getTextureRect().height){
            return true;
        }
    }
    return false;
}

bool MyDrawable::mouseIsOnScale(sf::Vector2i &mousePos){
    if(mousePos.x >= _spriteScale.getPosition().x && mousePos.x <= _spriteScale.getPosition().x+_spriteScale.getTextureRect().width){
        if(mousePos.y >= _spriteScale.getPosition().y && mousePos.y <= _spriteScale.getPosition().y+_spriteScale.getTextureRect().height){
            return true;
        }
    }
    return false;
}

bool MyDrawable::mouseIsOnDelete(sf::Vector2i &mousePos){
    if(mousePos.x >= _spriteDelete.getPosition().x && mousePos.x <= _spriteDelete.getPosition().x+_spriteDelete.getTextureRect().width){
        if(mousePos.y >= _spriteDelete.getPosition().y && mousePos.y <= _spriteDelete.getPosition().y+_spriteDelete.getTextureRect().height){
            return true;
        }
    }
    return false;
}

bool MyDrawable::mouseIsOn(sf::Vector2i &mousePos){
    if(mousePos.x >= _x && mousePos.x <= _x+_width){
        if(mousePos.y >= _y && mousePos.y <= _y+_height){
            return true;
        }
    }
    return false;
}


void MyDrawable::scaleByButtonScale(sf::Vector2i &mousePos){
    int width = abs(mousePos.x - _x);
    if(width <= _widthMin){
        width = _widthMin;
    }
    int height = abs(mousePos.y - _y);
    if(height <= _heightMin){
        height = _heightMin;
    }
    _width = width;
    _height = height;

    _spriteMove.setPosition(_x,_y);

    sf::Vector2u size = _spriteScale.getTexture()->getSize();
    _spriteScale.setPosition(_x+_width-size.x,_y+_height-size.y);

    size = _spriteDelete.getTexture()->getSize();
    _spriteDelete.setPosition(_x+_width-size.x,_y);

}

void MyDrawable::setPositionByButtonMove(sf::Vector2i &mousePos){
    _x = mousePos.x;
    _y = mousePos.y;

    _spriteMove.setPosition(_x,_y);

    sf::Vector2u size = _spriteScale.getTexture()->getSize();
    _spriteScale.setPosition(_x+_width-size.x,_y+_height-size.y);

    size = _spriteDelete.getTexture()->getSize();
    _spriteDelete.setPosition(_x+_width-size.x,_y);
}

void MyDrawable::saveOldCoo(){}
void MyDrawable::tpAllPersonIn(){}
