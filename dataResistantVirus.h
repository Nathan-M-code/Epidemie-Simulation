#ifndef DATARES_H_INCLUDED
#define DATARES_H_INCLUDED

#include "virus.h"

class DataResistantVirus{
public:
    DataResistantVirus(Virus *virus, bool resistant, int dayLeft);
    ~DataResistantVirus();
    Virus *_virus;
    bool _resistant;
    int _dayLeft;
};

#endif // DATARES_H_INCLUDED
