#include "community.h"

using namespace std;

Community::Community(int x, int y, unsigned width, unsigned height) : MyDrawable(x,y,width,height,150,100){
    _nbPerson = 200;
    for(unsigned i=0;i<_nbPerson;i++)
        _listPerson.push_back(new Person(_x,_y,_width,_height, 1));

    sf::Texture *texture = TextureLoader::getTextureGraphe();
    sf::Vector2u size = texture->getSize();
    _spriteGraphe.setTexture(*texture);
    _spriteGraphe.setPosition(_x+_width-size.x*2-5,_y+_height-size.y);

    _graphicsMenu = false;

    _virusMenu = false;
    _virusDisplayed = 0;
}

Community::Community(unsigned nbPerson, float speedPerson) : MyDrawable(0,0,400,400,150,100){
    _nbPerson = nbPerson;
    for(unsigned i=0;i<_nbPerson;i++)
        _listPerson.push_back(new Person(_x,_y,_width,_height,speedPerson));

    sf::Texture *texture = TextureLoader::getTextureGraphe();
    sf::Vector2u size = texture->getSize();
    _spriteGraphe.setTexture(*texture);
    _spriteGraphe.setPosition(_x+_width-size.x*2-5,_y+_height-size.y);

    _graphicsMenu = false;

    _virusMenu = false;
    _virusDisplayed = 0;
}


Community::~Community(){
    for(unsigned i=0;i<_listPerson.size();i++){
        delete _listPerson[i];
        _listPerson[i] = 0;
    }
}

bool Community::isGraphicsMenuOn(){
    return _graphicsMenu;
}
void Community::setGraphicsMenu(bool act){
    _graphicsMenu = act;
    if(_graphicsMenu){
        _listAllVirusConta = getAllVirusConta();
    }
}
int Community::clickOnGraphicsMenu(sf::Vector2i &mousePos){
    if(!(mousePos.x>=_spriteGraphe.getPosition().x && mousePos.x<=_spriteGraphe.getPosition().x+100)){
        return -1;
    }
    if(!(mousePos.y<=_spriteGraphe.getPosition().y && mousePos.y>=_spriteGraphe.getPosition().y-(_listAllVirusConta.size()+1)*25)){
        return -1;
    }
    return (_spriteGraphe.getPosition().y-mousePos.y)/25;
}

Virus* Community::getVirusByIndexOfMenu(int index){
    return _listAllVirusConta[index];
}

void Community::submitObserver(Graphic *graph){
    for(unsigned i=0;i<_listObserverGraphic.size();i++){
        if(_listObserverGraphic[i] == graph){
            return; //it is already in the list
        }
    }
    _listObserverGraphic.push_back(graph);
}

void Community::unsubmitObserverGraph(Graphic *graph){
    for(unsigned i=0;i<_listObserverGraphic.size();i++){
        if(_listObserverGraphic[i] == graph){
            _listObserverGraphic.erase(_listObserverGraphic.begin()+i);
        }
    }
}

void Community::notifyAllObservers(){
    for(unsigned i=0;i<_listObserverGraphic.size();i++){
        Virus *virusWanted = _listObserverGraphic[i]->getVirusWanted();
        if(virusWanted){
            DataGraphic4u data = this->getData(virusWanted);
            _listObserverGraphic[i]->addData(data);
        }else{
            DataGraphic4u data = this->getAllVirusData();
            _listObserverGraphic[i]->addData(data);
        }
    }
}

void Community::saveOldCoo(){
    _saveOldCoo = {_x,_y};
}

void Community::tpAllPersonIn(){
    int offsetX = _x-_saveOldCoo.x;
    int offsetY = _y-_saveOldCoo.y;
    for(unsigned i=0;i<_listPerson.size();i++){
        _listPerson[i]->move(offsetX, offsetY);
    }
}

void Community::contaminateARandom(Virus *virus){
    int index = rand_a_b(0,_listPerson.size());
    _listPerson[index]->contaminate(virus);
}

void Community::scaleByButtonScale(sf::Vector2i &mousePos){
    MyDrawable::scaleByButtonScale(mousePos);

    sf::Vector2u size = _spriteGraphe.getTexture()->getSize();
    _spriteGraphe.setPosition(_x+_width-size.x*2-5,_y+_height-size.y);

    for(unsigned i=0;i<_listPerson.size();i++){
        _listPerson[i]->updateCooCommu(_x,_y,_width,_height);
        if(!_listPerson[i]->isInTheCommu()){
            _listPerson[i]->tpRandom();
        }
    }
}

void Community::setPositionByButtonMove(sf::Vector2i &mousePos){
    MyDrawable::setPositionByButtonMove(mousePos);

    sf::Vector2u size = _spriteGraphe.getTexture()->getSize();
    _spriteGraphe.setPosition(_x+_width-size.x*2-5,_y+_height-size.y);

    for(unsigned i=0;i<_listPerson.size();i++){
        _listPerson[i]->updateCooCommu(_x,_y,_width,_height);
    }
}

bool Community::mouseIsOnGraph(sf::Vector2i &mousePos){
    if(mousePos.x >= _spriteGraphe.getPosition().x && mousePos.x <= _spriteGraphe.getPosition().x+_spriteGraphe.getTextureRect().width){
        if(mousePos.y >= _spriteGraphe.getPosition().y && mousePos.y <= _spriteGraphe.getPosition().y+_spriteGraphe.getTextureRect().height){
            return true;
        }
    }
    return false;
}

DataGraphic4u Community::getData(Virus *virus){
    unsigned healthy = 0;
    unsigned contaminated = 0;
    unsigned resistant = 0;
    unsigned dead = 0;
    for(unsigned i=0;i<_listPerson.size();i++){
        if(_listPerson[i]->isDead()){
            dead++;
        }else if(_listPerson[i]->isResistant(virus)){
            resistant++;
        }else if(_listPerson[i]->isContaminated(virus)){
            contaminated++;
        }else{
            healthy++;
        }
    }
    //cout << healthy << " " << contaminated << " " << resistant << " " << dead << endl;
    DataGraphic4u data(healthy,contaminated,resistant,dead);
    return data;
}

DataGraphic4u Community::getAllVirusData(){
    unsigned healthy = 0;
    unsigned contaminated = 0;
    unsigned resistant = 0;
    unsigned dead = 0;
    for(unsigned i=0;i<_listPerson.size();i++){
        if(_listPerson[i]->isDead()){
            dead++;
        }else if(_listPerson[i]->isContaminated()){
            contaminated++;
        }else{
            healthy++;
        }
    }
    //cout << healthy << " " << contaminated << " " << resistant << " " << dead << endl;
    DataGraphic4u data(healthy,contaminated,resistant,dead);
    return data;
}

std::vector<Virus *> Community::getAllVirusConta(){
    std::vector<Virus *> ret;
    for(unsigned i=0;i<_listPerson.size();i++){
        std::vector<Virus *> listVirusPersonConta = _listPerson[i]->getVirusConta();
        for(unsigned j=0;j<listVirusPersonConta.size();j++){
            unsigned k=0;
            bool already = false;
            while(k<ret.size()){
                if(ret[k] == listVirusPersonConta[j]){
                    already = true;
                    break;
                }
                k++;
            }
            if(!already){
                ret.push_back(listVirusPersonConta[j]);
            }
        }
    }
    return ret;
}

Virus* Community::getVirusDisplayed(){
    return _virusDisplayed;
}
void Community::setVirusDisplayed(Virus * virus){
    _virusDisplayed = virus;
}
void Community::setVirusMenu(bool act){
    _virusMenu = act;
    if(_virusMenu){
        _listAllVirusConta = getAllVirusConta();
    }
}
bool Community::isVirusMenuOn(){
    return _virusMenu;
}
bool Community::mouseIsOnVirus(sf::Vector2i &mousePos){
    if(mousePos.x >= _x && mousePos.x <= _x+100){
        if(mousePos.y >= _y+_height-20 && mousePos.y <= _y+_height){
            return true;
        }
    }
    return false;
}

int Community::clickOnVirusMenu(sf::Vector2i &mousePos){
    if(!(mousePos.x>=_x && mousePos.x<=_x+100)){
        return -1;
    }
    if(!(mousePos.y>=_y+_height-20-(_listAllVirusConta.size()+1)*25 && mousePos.y<=_y+_height-20)){
        return -1;
    }
    return (_y+_height-20-mousePos.y)/25;
}

void Community::udpate(){
    for(unsigned i=0;i<_listPerson.size();i++){
        _listPerson[i]->udpate(_listPerson);
    }
    //cout << "envoie info" << endl;
    notifyAllObservers();
    //cout << "apres envoie info" << endl;
}

void Community::draw(sf::RenderWindow &window){
    sf::RectangleShape rs;
    rs.setSize(sf::Vector2f(_width, _height));
    rs.setFillColor(sf::Color::Transparent);
    rs.setOutlineThickness(1);
    rs.setOutlineColor(sf::Color::White);
    rs.setPosition(_x,_y);

    window.draw(rs);

    for(unsigned i=0;i<_listPerson.size();i++){
        _listPerson[i]->draw(window, _virusDisplayed);
    }

    //buttons
    window.draw(_spriteMove);
    window.draw(_spriteScale);
    window.draw(_spriteGraphe);
    window.draw(_spriteDelete);

    //virus displayed
    rs.setSize(sf::Vector2f(100, 20));
    rs.setFillColor(sf::Color(100,100,100,150));
    rs.setPosition(_x,_y+_height-20);
    sf::Text virusName;
    virusName.setFont(*_font);
    virusName.setCharacterSize(16);
    if(_virusDisplayed == 0)
        virusName.setString("General");
    else
        virusName.setString(_virusDisplayed->getName());
    virusName.setPosition(_x+2,_y+_height-20);
    window.draw(rs);
    window.draw(virusName);

    if(_virusMenu){
        virusName.setString("General");
        rs.setSize(sf::Vector2f(100, 20));
        rs.setFillColor(sf::Color(100,100,100,150));
        rs.setPosition(_x,_y+_height-20-25);
        virusName.setPosition(_x+2,_y+_height-20-25);

        window.draw(rs);
        window.draw(virusName);

        for(unsigned i=0;i<_listAllVirusConta.size();i++){
            virusName.setString(_listAllVirusConta[i]->getName());
            rs.setPosition(_x,_y+_height-20-25*(i+2));
            virusName.setPosition(_x+2,_y+_height-20-25*(i+2));
            window.draw(rs);
            window.draw(virusName);
        }
    }


    //graphci menu
    if(_graphicsMenu){
        virusName.setString("General");
        rs.setSize(sf::Vector2f(100, 20));
        rs.setFillColor(sf::Color(100,100,100,150));
        rs.setPosition(_spriteGraphe.getPosition().x,_spriteGraphe.getPosition().y-25);
        virusName.setPosition(_spriteGraphe.getPosition().x+2,_spriteGraphe.getPosition().y-25);

        window.draw(rs);
        window.draw(virusName);

        for(unsigned i=0;i<_listAllVirusConta.size();i++){
            virusName.setString(_listAllVirusConta[i]->getName());
            rs.setPosition(_spriteGraphe.getPosition().x,_spriteGraphe.getPosition().y-25*(i+2));
            virusName.setPosition(_spriteGraphe.getPosition().x+2,_spriteGraphe.getPosition().y-25*(i+2));
            window.draw(rs);
            window.draw(virusName);
        }
    }
}
