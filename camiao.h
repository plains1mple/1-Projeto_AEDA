
//
// Created by caion on 14/10/2019.
//
#include <string>
using namespace std;

#ifndef PROJETO_AEDA_CAMIAO_H
#define PROJETO_AEDA_CAMIAO_H

#endif //PROJETO_AEDA_CAMIAO_H

class Camiao{
protected:
    int capacidade;
    string tipo;
public:
    virtual int getPrice();
    Camiao(int c, string tipo);
    //...

};

class Congelacao: public Camiao{
public:
    int getPrice();
    Congelacao();
    //...
};


class Perigosos: public Camiao{
private:
    string tipo;//inflamavel, toxica,...
    Perigosos();
    //...
};

class Normal: public Camiao{
public:
    Normal();
    int getPrice();
    //...

};


class Animais: public Camiao{
public:
    //...
};