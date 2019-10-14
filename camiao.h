//
// Created by caion on 14/10/2019.
//
#include <string>


#ifndef PROJETO_AEDA_CAMIAO_H
#define PROJETO_AEDA_CAMIAO_H

#endif //PROJETO_AEDA_CAMIAO_H

class Camiao{
protected:
    int capacidade;
    string tipo
public:
    virtual int getPrice();
    //...

};

class Congelacao: public Camiao{
public:
    int getPrice();

};


class Perigosos: public Camiao{
private:
    string tipo;//inflamavel, toxica,...
    //...
};


