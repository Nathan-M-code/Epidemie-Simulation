#include "dataResistantVirus.h"

DataResistantVirus::DataResistantVirus(Virus *virus, bool resistant, int dayLeft){
    _virus = virus;
    _resistant = resistant;
    _dayLeft = dayLeft;
}
DataResistantVirus::~DataResistantVirus(){}
