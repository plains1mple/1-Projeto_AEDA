#include "ServicoTransporte.h"
using namespace std;

double ServicoTransporte::NormalMultiplicador = 1;

double ServicoTransporte::CongelacaoMultiplicador = 2.5;

double ServicoTransporte::AnimaisMultiplicador = 3;

double ServicoTransporte::PerigososMultiplicador = 5;

string ServicoTransporte::getDestino() const {return destino;}

string ServicoTransporte::getOrigem() const {return origem;}

int ServicoTransporte::getId() const {return id;}

void ServicoTransporte::setHorario(string horario) {this->horario = horario;}

int ServicoTransporte::globalID = 1;

void ServicoTransporte::atualizaID() {globalID++;}

ServicoTransporte::ServicoTransporte(int id, string origem, string destino, string tipo_camioes, vector<Camiao *> camioes, string horario, Date data, unsigned disponivel) {
    this->id = id;
    this->origem = origem;
    this->destino = destino;
    this->camioes = camioes;
    this->horario = horario;
    this->tipo_camioes = tipo_camioes;
    this->data = data;
    this->servicoDisponivel = disponivel;
}

Date ServicoTransporte::getDate() const {return data;}

void ServicoTransporte::setDate(const Date &d) {this->data = d;}

void ServicoTransporte::setDestino(string destino) {
    this->destino = destino;
}

void ServicoTransporte::setOrigem(string origem) {
    this->origem = origem;
}

bool ServicoTransporte::operator==(ServicoTransporte st2) {
    return (this->id == st2.getId() && this->origem == st2.getOrigem() && this->destino == st2.getDestino());
}

string ServicoTransporte::getTipo() const {return tipo_camioes;}

vector <Camiao *> ServicoTransporte::getCamioes() const {return camioes;}

string ServicoTransporte::getHorario() const {return horario;}

ostream& operator<<(ostream &out, const ServicoTransporte &st) {
    out << "Identificador: " << st.getId() << endl;
    out << "Origem: " << st.getOrigem() << " ; Destino: " << st.getDestino() << endl;
    out << "Horario: " << st.getHorario() << endl;
    return out;
}

void ServicoTransporte::setCamioes(vector<Camiao *> camioes) {this->camioes = camioes;}

double ServicoTransporte::getDistancia(map<pair<string, string>, double> distancias) const{
    for (auto it = distancias.begin(); it != distancias.end(); it++){
        if (((*it).first.first == origem && (*it).first.second == destino) || ((*it).first.first == destino && (*it).first.second == origem))
            return (*it).second;
    }
}

double ServicoTransporte::getPreco(map<pair<string,string>,double > distancias) const {
    double result = this->getDistancia(distancias)*this->getCamioes().size();
    if (this->getTipo() == "perigosos") result *= this->PerigososMultiplicador;
    else if (this->getTipo() == "congelacao") result *= this->CongelacaoMultiplicador;
    else if (this->getTipo() == "normal") result*= this->NormalMultiplicador;
    else if (this->getTipo() == "animais") result *= this->AnimaisMultiplicador;
    return result;
}

void ServicoTransporte::setId(int id) {this->id = id;}

bool Date::operator==(const Date &d1) {
    return (d1.ano == this->ano && d1.mes == this->mes && d1.dia == this->dia);
}

void ServicoTransporte::setDisponibilidade(unsigned b) {
    this->servicoDisponivel = b;
}

//verifica se o servico se encontra disponivel
unsigned ServicoTransporte::getDisponibilidade() const {
    return servicoDisponivel;
}

bool Date::operator<(const Date &d1) {
    int aux1 = this->ano*365 + this->mes*30 +this->dia;
    int aux2 = d1.ano*365 + d1.mes*30 + d1.dia;
    return aux1<aux2;
}

LocalizacaoIndisponivel::LocalizacaoIndisponivel(string nome) {this->nome = nome;}

string LocalizacaoIndisponivel::getNome() const {return nome;}

CamioesIndisponiveis::CamioesIndisponiveis() {}

ServicoInexistente::ServicoInexistente(string origem, string destino) {
    this->origem = origem;
    this->destino = destino;
}

string ServicoInexistente::getDestino() const {return destino;}

string ServicoInexistente::getOrigem() const {return origem;}

MotoristasIndisponiveis::MotoristasIndisponiveis(string origem, string destino) {
    this->origem = origem;
    this->destino = destino;
}
