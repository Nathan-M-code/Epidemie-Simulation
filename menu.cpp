#include "menu.h"

using namespace std;

Menu::Menu(int x, int y, unsigned width, unsigned height) : MyDrawable(x,y,width,height,300,300){
    _rsBackground.setSize(sf::Vector2f(width, height));
    _rsBackground.setFillColor(sf::Color(100,100,100,150));
    _rsBackground.setPosition(x,y);


    _rsNewVirus.setSize(sf::Vector2f(100, 30));
    _rsNewVirus.setFillColor(sf::Color(200,200,200,100));
    _rsNewVirus.setPosition(_x+_width/2-_width/4-100/2,_y+_height-30);

    _rsNewCommu.setSize(sf::Vector2f(100, 30));
    _rsNewCommu.setFillColor(sf::Color(200,200,200,100));
    _rsNewCommu.setPosition(_x+_width/2+_width/4-100/2,_y+_height-30);

    _text.setFont(*_font);
    _text.setCharacterSize(11);

    _listCursor.push_back(new Cursor(_x+_width/4-50,_y+50,100,30,0,100)); //_contagion
    _listCursor.push_back(new Cursor(_x+_width/4-50,_y+100,100,30,0,100)); //_death
    _listCursor.push_back(new Cursor(_x+_width/4-50,_y+150,100,30,3,100)); //_distanceContagion
    _listCursor.push_back(new Cursor(_x+_width/4-75,_y+200,150,30,1,5000)); //_dayLeft
    _tb = new TextBox(_x+_width/4-50,_y+230,"NameVirus");

    _listCursor.push_back(new Cursor(_x+3*_width/4-60,_y+50,120,30,2,600)); //nbPerson
    _cursorFloat = new CursorFloat(_x+3*_width/4-60,_y+100,120,30,0,30); //speed person


}
Menu::~Menu(){
    for(unsigned i=0;i<_listCursor.size();i++){
        delete _listCursor[i];
    }
    delete _tb;
    delete _cursorFloat;
}
void Menu::setPositionByButtonMove(sf::Vector2i &mousePos){
    MyDrawable::setPositionByButtonMove(mousePos);
    _rsBackground.setPosition(_x,_y);
    _rsNewVirus.setPosition(_x+_width/2-_width/4-100/2,_y+_height-30);
    _rsNewCommu.setPosition(_x+_width/2+_width/4-100/2,_y+_height-30);

    _listCursor[0]->setPosition(_x+_width/4-50,_y+50);
    _listCursor[1]->setPosition(_x+_width/4-50,_y+100);
    _listCursor[2]->setPosition(_x+_width/4-50,_y+150);
    _listCursor[3]->setPosition(_x+_width/4-75,_y+200);
    _tb->setPos(sf::Vector2f(_x+_width/4-50,_y+230));

    _listCursor[4]->setPosition(_x+3*_width/4-60,_y+50);
    _cursorFloat->setPosition(_x+3*_width/4-60,_y+100);
}
void Menu::scaleByButtonScale(sf::Vector2i &mousePos){
    MyDrawable::scaleByButtonScale(mousePos);
    _rsBackground.setSize(sf::Vector2f(_width, _height));
    _rsNewVirus.setPosition(_x+_width/2-_width/4-100/2,_y+_height-30);
    _rsNewCommu.setPosition(_x+_width/2+_width/4-100/2,_y+_height-30);

    _listCursor[0]->setPosition(_x+_width/4-50,_y+50);
    _listCursor[1]->setPosition(_x+_width/4-50,_y+100);
    _listCursor[2]->setPosition(_x+_width/4-50,_y+150);
    _listCursor[3]->setPosition(_x+_width/4-75,_y+200);
    _tb->setPos(sf::Vector2f(_x+_width/4-50,_y+230));

    _listCursor[4]->setPosition(_x+3*_width/4-60,_y+50);
    _cursorFloat->setPosition(_x+3*_width/4-60,_y+100);
}

void Menu::clickNonButton(bool pressed, sf::Vector2i &mousePos){
    for(unsigned i=0;i<_listCursor.size();i++){
        if(pressed){
            if(_listCursor[i]->mouseIsOnCursor(mousePos)){
                _listCursor[i]->setActivated(true);
            }
        }else{
            _listCursor[i]->setActivated(false);
        }
    }

    if(pressed){
        if(_cursorFloat->mouseIsOnCursor(mousePos)){
            _cursorFloat->setActivated(true);
        }
    }else{
        _cursorFloat->setActivated(false);
    }

    if(!pressed){

    }

    if(pressed){
        if(_tb->testClick(mousePos.x, mousePos.y)){
            _tb->setFocus(true);
        }else{
            _tb->setFocus(false);
        }
    }
}

void Menu::writeKey(sf::Uint32 &key){
    //cout << key << endl;
    if(_tb->isFocus()){
        if((key>=48 && key<=57) || (key>=97 && key<=122) || (key>=64 && key<=90) || key == 8){
            if(key != 8){
                _tb->ajouterLettre(key);
            }else{
                _tb->supprimerLettre();
            }
        }
    }
}

void Menu::handlerMouseMotion(sf::Vector2i &mousePos){
    for(unsigned i=0;i<_listCursor.size();i++){
        if(_listCursor[i]->isActivated()){
            _listCursor[i]->setValue(mousePos);
        }
    }
    if(_cursorFloat->isActivated()){
        _cursorFloat->setValue(mousePos);
    }
}

bool Menu::mouseIsOnNewVirus(sf::Vector2i &mousePos){
    if(mousePos.x >= _rsNewVirus.getPosition().x && mousePos.x <= _rsNewVirus.getPosition().x+_rsNewVirus.getLocalBounds().width){
        if(mousePos.y >= _rsNewVirus.getPosition().y && mousePos.y <= _rsNewVirus.getPosition().y+_rsNewVirus.getLocalBounds().height){
            return true;
        }
    }
    return false;
}
bool Menu::mouseIsOnNewCommu(sf::Vector2i &mousePos){
    if(mousePos.x >= _rsNewCommu.getPosition().x && mousePos.x <= _rsNewCommu.getPosition().x+_rsNewCommu.getLocalBounds().width){
        if(mousePos.y >= _rsNewCommu.getPosition().y && mousePos.y <= _rsNewCommu.getPosition().y+_rsNewCommu.getLocalBounds().height){
            return true;
        }
    }
    return false;
}

Virus* Menu::getNewVirus(){
    return new Virus(_tb->getString(), _listCursor[0]->getValue()/100.0, _listCursor[1]->getValue()/100.0,_listCursor[2]->getValue(), _listCursor[3]->getValue());
}
Community* Menu::getNewCommunity(){
    return new Community(_listCursor[4]->getValue(),_cursorFloat->getValue());
}

void Menu::draw(sf::RenderWindow &window){

    window.draw(_rsBackground);

    window.draw(_rsNewVirus);
    window.draw(_rsNewCommu);

    _text.setString("Menu");
    _text.setPosition(_x+_width/2-_text.getLocalBounds().width/2,_y);
    window.draw(_text);

    _text.setString("+Virus");
    _text.setPosition(_rsNewVirus.getPosition().x+_rsNewVirus.getSize().x/2-_text.getLocalBounds().width/2,_rsNewVirus.getPosition().y+_rsNewVirus.getSize().y/2-_text.getLocalBounds().height/2);
    window.draw(_text);

    _text.setString("+Commu");
    _text.setPosition(_rsNewCommu.getPosition().x+_rsNewCommu.getSize().x/2-_text.getLocalBounds().width/2,_rsNewCommu.getPosition().y+_rsNewCommu.getSize().y/2-_text.getLocalBounds().height/2);
    window.draw(_text);

    _text.setString("% Contagion");
    _text.setPosition(_listCursor[0]->getPosition().x+_listCursor[0]->getSize().x/2-_text.getLocalBounds().width/2,_listCursor[0]->getPosition().y-_text.getLocalBounds().height);
    window.draw(_text);

    _text.setString("% Death");
    _text.setPosition(_listCursor[1]->getPosition().x+_listCursor[1]->getSize().x/2-_text.getLocalBounds().width/2,_listCursor[1]->getPosition().y-_text.getLocalBounds().height);
    window.draw(_text);

    _text.setString("Dist Contagion");
    _text.setPosition(_listCursor[2]->getPosition().x+_listCursor[2]->getSize().x/2-_text.getLocalBounds().width/2,_listCursor[2]->getPosition().y-_text.getLocalBounds().height);
    window.draw(_text);

    _text.setString("Day Left");
    _text.setPosition(_listCursor[3]->getPosition().x+_listCursor[3]->getSize().x/2-_text.getLocalBounds().width/2,_listCursor[3]->getPosition().y-_text.getLocalBounds().height);
    window.draw(_text);

    _tb->draw(window);

    _text.setString("Nb person");
    _text.setPosition(_listCursor[4]->getPosition().x+_listCursor[4]->getSize().x/2-_text.getLocalBounds().width/2,_listCursor[4]->getPosition().y-_text.getLocalBounds().height);
    window.draw(_text);

    _text.setString("Speed person");
    _text.setPosition(_cursorFloat->getPosition().x+_cursorFloat->getSize().x/2-_text.getLocalBounds().width/2,_cursorFloat->getPosition().y-_text.getLocalBounds().height);
    window.draw(_text);

    for(unsigned i=0;i<_listCursor.size();i++){
        _listCursor[i]->draw(window);
    }
    _cursorFloat->draw(window);

    window.draw(_spriteMove);
    window.draw(_spriteScale);
    window.draw(_spriteDelete);
}
