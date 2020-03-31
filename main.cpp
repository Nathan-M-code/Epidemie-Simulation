#include "TextureLoader.h"
#include "graphic.h"
#include "menu.h"

using namespace std;

void removeDrawable(MyDrawable *mdraw, Menu *menu,  vector<MyDrawable *> &listMyDrawable, vector<Community *> &listCommunity, vector<Graphic *> &listGraphic, vector<Virus *> &listVirus){
    if(mdraw == menu)
        return;

    bool isVirus = false;
    for(unsigned i=0;i<listMyDrawable.size();i++){
        if(listMyDrawable[i] == mdraw)
            listMyDrawable.erase(listMyDrawable.begin()+i);
    }
    for(unsigned i=0;i<listCommunity.size();i++){
        if(listCommunity[i] == mdraw)
            listCommunity.erase(listCommunity.begin()+i);
    }
    for(unsigned i=0;i<listGraphic.size();i++){
        if(listGraphic[i] == mdraw){
            for(unsigned j=0;j<listCommunity.size();j++){
                listCommunity[j]->unsubmitObserverGraph(listGraphic[i]);
            }
            listGraphic.erase(listGraphic.begin()+i);
        }
    }
    for(unsigned i=0;i<listVirus.size();i++){
        if(listVirus[i] == mdraw){
            listVirus.erase(listVirus.begin()+i);
            isVirus = true;
        }
    }
    if(!isVirus)
        delete mdraw;
}

void unlinkGraphic(Graphic *g, vector<Community *> &listCommunity){
    for(unsigned i=0;i<listCommunity.size();i++){
        listCommunity[i]->unsubmitObserverGraph(g);
    }
}

int main(){
    srand(time(NULL));

    sf::Vector2i tailleEcran(1280,720);
    int HH = tailleEcran.y/2;
    int HW = tailleEcran.x/2;

    TextureLoader::init();

    /*sf::Text text_camera;
    text_camera.setFont(*TextureLoader::getFont());
    text_camera.setFillColor(sf::Color(255,255,255));
    text_camera.setCharacterSize(16);*/

    sf::Vector2i mousePos;

    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(tailleEcran.x,tailleEcran.y), "SimuEpidemie", sf::Style::Close);

    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    unsigned indexToScale = 0;
    bool pressedScale = false;
    unsigned indexToMove = 0;
    bool pressedMove = false;

    vector<MyDrawable *> listMyDrawable;
    vector<Community *> listCommunity;
    vector<Graphic *> listGraphic;
    vector<Virus *> listVirus;

    /*Community *cm = new Community(300,100,400,300);
    listMyDrawable.push_back(cm);
    listCommunity.push_back(cm);*/

    /*Virus *v = new Virus("COVID-19");
    listMyDrawable.push_back(v);
    listVirus.push_back(v);

    v = new Virus("Test");
    listMyDrawable.push_back(v);
    listVirus.push_back(v);*/

    Menu *menu = new Menu(0,0,300,300);
    listMyDrawable.push_back(menu);

    sf::Uint32 key;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape){
                        window.close();
                    }
                    //-----------------------------------
                    if (event.key.code == sf::Keyboard::T){
                        //listCommunity[0]->contaminateARandom(virus);
                    }
                    //----------------gameplay----------------

                    //--------------------------------

                    //--------------------------------

                    //------------------test-----------------
                    break;
                /*case sf::Event::KeyReleased:

                    break;*/
                case sf::Event::MouseMoved:
                    mousePos = sf::Mouse::getPosition(window);
                    for(unsigned i=0;i<listVirus.size();i++){
                        if(listVirus[i]->isArrowDisplayed()){
                            listVirus[i]->setObjectifArrow(mousePos);
                        }
                    }
                    menu->handlerMouseMotion(mousePos);
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left){
                        mousePos = sf::Mouse::getPosition(window);
                        //menu
                        menu->clickNonButton(true, mousePos);
                        if(menu->mouseIsOnNewVirus(mousePos)){
                            Virus *v = menu->getNewVirus();
                            listMyDrawable.push_back(v);
                            listVirus.push_back(v);
                        }else if(menu->mouseIsOnNewCommu(mousePos)){
                            Community *cm = menu->getNewCommunity();
                            listMyDrawable.push_back(cm);
                            listCommunity.push_back(cm);
                        }

                        //scaling and moving
                        for(unsigned i=0;i<listMyDrawable.size();i++){
                            if(listMyDrawable[i]->mouseIsOnDelete(mousePos)){
                                removeDrawable(listMyDrawable[i], menu, listMyDrawable, listCommunity, listGraphic, listVirus);
                                break;
                            }else if(listMyDrawable[i]->mouseIsOnMove(mousePos)){
                                listMyDrawable[i]->saveOldCoo();
                                pressedMove = true;
                                indexToMove = i;
                            }else if(listMyDrawable[i]->mouseIsOnScale(mousePos)){
                                pressedScale = true;
                                indexToScale = i;
                            }
                        }

                        //button graphe of commu
                        for(unsigned i=0;i<listCommunity.size();i++){
                            if(listCommunity[i]->isGraphicsMenuOn()){
                                int index = listCommunity[i]->clickOnGraphicsMenu(mousePos);
                                //cout << index << endl;
                                if(index != -1){
                                    Graphic *graphe = 0;
                                    if(index == 0){
                                        graphe = new Graphic(10,10,200,100,nullptr);

                                    }else{
                                        graphe = new Graphic(10,10,200,100,listCommunity[i]->getVirusByIndexOfMenu(index-1));
                                    }
                                    listMyDrawable.push_back(graphe);
                                    listGraphic.push_back(graphe);
                                    listCommunity[i]->submitObserver(graphe);
                                }
                                listCommunity[i]->setGraphicsMenu(false);
                            }else if(listCommunity[i]->isVirusMenuOn()){
                                int index = listCommunity[i]->clickOnVirusMenu(mousePos);
                                //cout << index << endl;
                                if(index != -1){
                                    if(index == 0){
                                        listCommunity[i]->setVirusDisplayed(nullptr);

                                    }else{
                                        listCommunity[i]->setVirusDisplayed(listCommunity[i]->getVirusByIndexOfMenu(index-1));
                                    }
                                }
                                listCommunity[i]->setVirusMenu(false);
                            }else if(listCommunity[i]->mouseIsOnGraph(mousePos)){
                                listCommunity[i]->setGraphicsMenu(true);
                            }else if(listCommunity[i]->mouseIsOnVirus(mousePos)){
                                listCommunity[i]->setVirusMenu(true);
                            }
                        }

                        //button arrow of virus
                        for(unsigned i=0;i<listVirus.size();i++){
                            if(listVirus[i]->mouseIsOnConta(mousePos)){
                                listVirus[i]->setArrowDisplayed(true);
                                listVirus[i]->setObjectifArrow(mousePos);
                            }
                        }

                        //button unlike of graph
                        for(unsigned i=0;i<listGraphic.size();i++){
                            if(listGraphic[i]->mouseIsOnUnlink(mousePos)){
                                unlinkGraphic(listGraphic[i], listCommunity);
                            }
                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left){
                        if(pressedScale){
                            pressedScale = false;
                        }
                        if(pressedMove){
                            pressedMove = false;
                            listMyDrawable[indexToMove]->tpAllPersonIn();
                        }
                        for(unsigned i=0;i<listVirus.size();i++){
                            if(listVirus[i]->isArrowDisplayed()){
                                for(unsigned j=0;j<listCommunity.size();j++){
                                    if(listCommunity[j]->mouseIsOn(mousePos)){
                                        listCommunity[j]->contaminateARandom(listVirus[i]);
                                        //show the virus in community
                                        listCommunity[j]->setVirusDisplayed(listVirus[i]);
                                        //new grpahic
                                        Graphic *graphe = new Graphic(10,10,200,100,listVirus[i]);
                                        listMyDrawable.push_back(graphe);
                                        listGraphic.push_back(graphe);
                                        listCommunity[j]->submitObserver(graphe);
                                    }
                                }
                                listVirus[i]->setArrowDisplayed(false);
                            }
                        }
                        menu->clickNonButton(false, mousePos);
                    }
                    break;
                /*case sf::Event::MouseWheelMoved:
                    if(event.mouseWheel.delta>0){ //zoom in delta>0
                        //test
                    }else if(event.mouseWheel.delta<0){ //zoom out delat<0
                        //test
                    }
                    break;*/
                case sf::Event::TextEntered:
                    key = event.text.unicode;
                    menu->writeKey(key);
                    break;
                default:
                    break;
            }
        }
        //logique
        if(pressedScale){
            listMyDrawable[indexToScale]->scaleByButtonScale(mousePos);
        }
        if(pressedMove){
            listMyDrawable[indexToMove]->setPositionByButtonMove(mousePos);
        }

        for(unsigned i=0;i<listCommunity.size();i++){
            listCommunity[i]->udpate();
        }

        //clear
        window.clear();

        //draw
        for(unsigned i=0;i<listCommunity.size();i++){
            listCommunity[i]->draw(window);
        }
        for(unsigned i=0;i<listGraphic.size();i++){
            listGraphic[i]->draw(window);
        }
        for(unsigned i=0;i<listVirus.size();i++){
            listVirus[i]->drawIcon(window);
        }
        menu->draw(window);


        //Text
        // Set the default view back
        /*text_camera.setString("mouse: x: "+intToString(mousePos.x)+" y: "+intToString(mousePos.y));
        text_camera.setPosition(0,0);
        window.draw(text_camera);*/

        window.display();
    }

    return 0;
}

