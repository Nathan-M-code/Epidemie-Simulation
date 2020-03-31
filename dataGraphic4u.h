#ifndef DATAGRAPH4U_H_INCLUDED
#define DATAGRAPH4U_H_INCLUDED

class DataGraphic4u{
public:
    DataGraphic4u(unsigned healthy, unsigned contaminated, unsigned resistant, unsigned dead);
    unsigned healthy;
    unsigned contaminated;
    unsigned resistant;
    unsigned dead;

    unsigned getNbTot();
};


#endif // DATAGRAPH4U_H_INCLUDED
