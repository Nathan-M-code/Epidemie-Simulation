#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include "virus.h"
#include "dataResistantVirus.h"

class Person{
public:
    Person(int xmin, int ymin, int width, int height, float speed);
    ~Person();

    sf::Vector2f getPos();
    bool isDead();
    bool isResistant(Virus *virus);
    bool isContaminated(Virus *virus);
    bool isContaminated();
    std::vector<Virus *> getVirusConta();

    void move(int offsetX, int offsetY);

    void contaminate(Virus *virus);
    bool hasVirus(Virus *virus);

    void updateCooCommu(int xmin, int ymin, int width, int height);
    void tpRandom();
    bool isInTheCommu();

    void udpate(std::vector<Person*> listPersonCommu);

    void draw(sf::RenderWindow &window, Virus *virus);
private:
    unsigned _age;
    bool _dead;

    std::vector<DataResistantVirus*> _listDataResistantVirus;

    std::vector<Virus*> _listVirusConta;
    std::vector<Person*> _listNearbyPerson;

    unsigned _radius;

    int _xmin;
    int _ymin;
    int _xmax;
    int _ymax;

    int _objX;
    int _objY;

    float _speed;

    sf::CircleShape _cs;
    sf::Vector2f _pos;

    bool isCloseToObjectif();
    bool isAlreadyClose(Person *person);
    void removePersonFromListClose(Person *person);
    void removeVirus(Virus *virus);
};


#endif // PERSON_H_INCLUDED
