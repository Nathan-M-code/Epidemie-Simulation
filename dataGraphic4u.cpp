#include "dataGraphic4u.h"

DataGraphic4u::DataGraphic4u(unsigned healthy, unsigned contaminated, unsigned resistant, unsigned dead){
    this->healthy = healthy;
    this->contaminated = contaminated;
    this->resistant = resistant;
    this->dead = dead;
}

unsigned DataGraphic4u::getNbTot(){
    return healthy+contaminated+resistant+dead;
}
