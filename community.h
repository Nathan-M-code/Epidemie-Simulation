#ifndef COMMU_H_INCLUDED
#define COMMU_H_INCLUDED

#include "person.h"
#include "dataGraphic4u.h"
#include "myDrawable.h"
#include "graphic.h"

class Community : public MyDrawable{
public:
    Community(int x, int y, unsigned width, unsigned height);
    Community(unsigned nbPerson, float speedPerson);
    ~Community();

    bool mouseIsOnGraph(sf::Vector2i &mousePos);
    bool isGraphicsMenuOn();
    void setGraphicsMenu(bool act);
    int clickOnGraphicsMenu(sf::Vector2i &mousePos);

    Virus* getVirusByIndexOfMenu(int index);

    void submitObserver(Graphic *graph);
    void unsubmitObserverGraph(Graphic *graph);
    void notifyAllObservers();

    void contaminateARandom(Virus *virus);
    DataGraphic4u getData(Virus *virus);
    DataGraphic4u getAllVirusData();

    std::vector<Virus *> getAllVirusConta();

    void setPositionByButtonMove(sf::Vector2i &mousePos);
    void scaleByButtonScale(sf::Vector2i &mousePos);
    void saveOldCoo();
    void tpAllPersonIn();

    Virus *getVirusDisplayed();
    void setVirusDisplayed(Virus * virus);
    void setVirusMenu(bool act);
    bool isVirusMenuOn();
    bool mouseIsOnVirus(sf::Vector2i &mousePos);
    int clickOnVirusMenu(sf::Vector2i &mousePos);

    void udpate();

    void draw(sf::RenderWindow &window);
private:
    unsigned _nbPerson;
    std::vector<Person*> _listPerson;

    sf::Sprite _spriteGraphe;

    sf::Vector2u _saveOldCoo;

    std::vector<Graphic *> _listObserverGraphic;

    bool _graphicsMenu;
    std::vector<Virus *> _listAllVirusConta;

    bool _virusMenu;
    Virus *_virusDisplayed;
};

#endif // COMMU_H_INCLUDED
