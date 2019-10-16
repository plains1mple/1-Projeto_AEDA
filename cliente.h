//
// Created by caion on 14/10/2019.
//
#include "Servico_transporte.h"
#include <string>

#ifndef PROJETO_AEDA_CLIENTE_H
#define PROJETO_AEDA_CLIENTE_H

#endif //PROJETO_AEDA_CLIENTE_H


class Cliente{
private:
    string nome;
    int nif;
    vector <ServicoTransporte> servicos;//servicos requisitados pelo cliente
    //...
public:
    Cliente(string nome, int nif);

};

