#include "person.h"

using namespace std;

Person::Person(int xmin, int ymin, int width, int height){
    _age = rand_a_b(1,100);
    _dead = false;

    _xmin = xmin;
    _ymin = ymin;
    _xmax = xmin+width;
    _ymax = ymin+height;

    _speed = 0.8;

    _radius = 5;
    int x = rand_a_b(_xmin,_xmax+1-_radius*2);
    int y = rand_a_b(_ymin,_ymax+1-_radius*2);
    _objX = x;
    _objY = y;
    _pos = {x,y};
    _cs.setRadius(_radius);
}
Person::~Person(){
    for(unsigned i=0;i<_listDataResistantVirus.size();i++){
        delete _listDataResistantVirus[i];
        _listDataResistantVirus[i] = 0;
    }
}

void Person::move(int offsetX, int offsetY){
    _pos = {_pos.x+offsetX,_pos.y+offsetY};
    _cs.setPosition(_pos.x , _pos.y);
    int x = rand_a_b(_xmin,_xmax+1-_radius*2);
    int y = rand_a_b(_ymin,_ymax+1-_radius*2);
    _objX = x;
    _objY = y;
}

void Person::updateCooCommu(int xmin, int ymin, int width, int height){
    _xmin = xmin;
    _ymin = ymin;
    _xmax = xmin+width;
    _ymax = ymin+height;
    int x = rand_a_b(_xmin,_xmax+1-_radius*2);
    int y = rand_a_b(_ymin,_ymax+1-_radius*2);
    _objX = x;
    _objY = y;
}

void Person::tpRandom(){
    int x = rand_a_b(_xmin,_xmax+1-_radius*2);
    int y = rand_a_b(_ymin,_ymax+1-_radius*2);
    _pos = {x,y};
    _objX = x;
    _objY = y;
    _cs.setPosition(x,y);
}

bool Person::isInTheCommu(){
    if(_pos.x >= _xmin && _pos.x <= _xmax){
        if(_pos.y >= _ymin && _pos.y <= _ymax){
            return true;
        }
    }
    return false;
}

void Person::contaminate(Virus *virus){
    if(!hasVirus(virus) && !_dead && !isResistant(virus)){
        _listVirusConta.push_back(virus);
        DataResistantVirus *dataRes = new DataResistantVirus(virus,false,virus->getDayLeft());
        _listDataResistantVirus.push_back(dataRes);
    }

}

bool Person::hasVirus(Virus *virus){
    for(unsigned i=0;i<_listVirusConta.size();i++){
        if(_listVirusConta[i] == virus)
            return true;
    }
    return false;
}

void Person::udpate(std::vector<Person*> listPersonCommu){
    if(_dead)
        return;

    //cout << "obj: " << _objX << " " << _objY << endl;
    //cout << "_pos: " << _pos.x << " " << _pos.y << endl;
    if(isCloseToObjectif()){
        _objX = rand_a_b(_xmin,_xmax+1-_radius*2);
        _objY = rand_a_b(_ymin,_ymax+1-_radius*2);
        //cout << "obj: " << _objX << " " << _objY << endl;
    }

    float radians = atan2((int)(_objY-_pos.y), (int)(_objX-_pos.x));

    float directionX = cos(radians)*_speed;
    float directionY = sin(radians)*_speed;
    //cout << directionX << endl;
    //cout << directionY << endl;

    _pos = {_pos.x+directionX,_pos.y+directionY};
    _cs.setPosition(_pos.x , _pos.y);

    //virus transmission
    for(unsigned i=0;i<_listVirusConta.size();i++){
        for(unsigned j=0;j<listPersonCommu.size();j++){
            if(listPersonCommu[j]!=this){
                sf::Vector2f posBis = listPersonCommu[j]->getPos();
                float dist = distance(posBis, _pos);
                if(isAlreadyClose(listPersonCommu[j])){
                    if(dist > _listVirusConta[i]->getDistanceConta()){
                        removePersonFromListClose(listPersonCommu[j]);
                    }
                }else{
                    if(dist <= _listVirusConta[i]->getDistanceConta()){
                        _listNearbyPerson.push_back(listPersonCommu[j]);
                        int rnd = rand_a_b(0,100);
                        if(rnd < _listVirusConta[i]->getContagion()*100)
                            listPersonCommu[j]->contaminate(_listVirusConta[i]);
                    }
                }
            }
        }
    }

    for(unsigned i=0;i<_listDataResistantVirus.size();i++){
        if(!_listDataResistantVirus[i]->_resistant){
            if(_listDataResistantVirus[i]->_dayLeft > 0){
                _listDataResistantVirus[i]->_dayLeft--;
            }else{
                int rnd = rand_a_b(0,100);
                if(rnd <= _listDataResistantVirus[i]->_virus->getDeath()*100){
                    _dead = true;
                }else{
                    _listDataResistantVirus[i]->_resistant = true;
                    removeVirus(_listDataResistantVirus[i]->_virus);
                }
            }
        }
    }
}

bool Person::isCloseToObjectif(){
    if(int(_pos.x)-round(_speed) <= _objX && int(_pos.x)+round(_speed) >= _objX && int(_pos.y)-round(_speed) <= _objY && int(_pos.y)+round(_speed) >= _objY){
        return true;
    }
    return false;
}

bool Person::isAlreadyClose(Person *person){
    for(unsigned i=0;i<_listNearbyPerson.size();i++){
        if(_listNearbyPerson[i] == person)
            return true;
    }
    return false;
}

void Person::removePersonFromListClose(Person *person){
    for(unsigned i=0;i<_listNearbyPerson.size();i++){
        if(_listNearbyPerson[i] == person)
            _listNearbyPerson.erase(_listNearbyPerson.begin()+i);
    }
}

void Person::removeVirus(Virus *virus){
    for(unsigned i=0;i<_listVirusConta.size();i++){
        if(_listVirusConta[i] == virus){
            _listVirusConta.erase(_listVirusConta.begin()+i);
        }
    }
}


void Person::draw(sf::RenderWindow &window, Virus *virus){
    sf::Color color;
    if(virus){
        if(_dead){
            color = sf::Color(100,100,100);
        }else if(isResistant(virus)){
            color = sf::Color::Green;
        }else if(isContaminated(virus)){
            color = sf::Color::Red;
        }else{
            color = sf::Color::Blue;
        }
    }else{ //general (dont show resistant)
        if(_dead){
            color = sf::Color(100,100,100);
        }else if(isContaminated()){
            color = sf::Color::Red;
        }else{
            color = sf::Color::Blue;
        }
    }

    _cs.setFillColor(color);


    window.draw(_cs);

}

//----------------------------------------------------------------
sf::Vector2f Person::getPos(){
    return _pos;
}

bool Person::isDead(){
    return _dead;
}
bool Person::isResistant(Virus *virus){
    for(unsigned i=0;i<_listDataResistantVirus.size();i++){
        if(_listDataResistantVirus[i]->_virus == virus){
            if(_listDataResistantVirus[i]->_resistant){
                return true;
            }else{
                return false;
            }
        }
    }
    return false;
}
bool Person::isContaminated(){
    return _listVirusConta.size()>0;
}

bool Person::isContaminated(Virus *virus){
    for(unsigned i=0;i<_listVirusConta.size();i++){
        if(_listVirusConta[i] == virus){
            return true;
        }
    }
    return false;
}

std::vector<Virus *> Person::getVirusConta(){
    return _listVirusConta;
}
