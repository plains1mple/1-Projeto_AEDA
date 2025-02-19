#include "Person.h"
#include "Utils.h"
#include <sstream>

using namespace std;
unsigned Motorista::last_id = 0;

Person::Person(string name, int age) {
    this->name = name;
    this->age = age;
}

void Person::setAge(int age) {this->age = age;}

void Person::setName(string name) {this->name = name;}

Cliente::Cliente(string name, int age, int nif, vector<ServicoTransporte> servicos_adquiridos) : Person(name,age){
    this->nif = nif;
    this->servicos_adquiridos = servicos_adquiridos;
}

Cliente::Cliente(string name, int age, int nif): Person(name, age) {
    this->nif = nif;
}

int Cliente::getNif() const { return nif;}

void Cliente::setNif(int nif) {this->nif = nif;}

void Cliente::setServicos(vector<ServicoTransporte> servicos) {this->servicos_adquiridos = servicos;}

void Cliente::addServico(ServicoTransporte servico) {
    this->servicos_adquiridos.push_back(servico);
}

vector<ServicoTransporte> Cliente::getServicos() const {return servicos_adquiridos;}


int Motorista::getSalario() const {
    return salario;
}


Motorista::Motorista(string name, int age, int salario, pair<string, string> horario, vector<char> categorias) : Person(name, age) {
    this->id = ++last_id;
    this->salario = salario;
    this->horario = horario;
    this->categorias = categorias;
}

bool Cliente::operator==(const Cliente c2) {
    return (this->name == c2.getName() && this->nif == c2.getNif());
}

bool Motorista::isWorking(string time) const {
    istringstream str(time);
    string token;
    istringstream inicio(horario.first);
    istringstream fim(horario.second);
    return compareTime(str, inicio, fim);
}

pair <string, string> Motorista::getHorario() const {
    return horario;
}

vector<char> Motorista::getCategorias() const {
    return categorias;
}

unsigned Motorista::getId() const {
    return id;
}

unsigned Motorista::getLastId() {
    return last_id;
}

void Motorista::setSalario(int salary) {
    this->salario = salary;
}

void Motorista::setHorario(pair<string, string> time) {
    this->horario = time;
}

void Motorista::setHorario(string inicio, string fim) {
    this->horario.first = inicio;
    this->horario.second = fim;
}

void Motorista::setCategorias(vector<char> category) {
    this->categorias = category;
}

bool Motorista::operator==(const Motorista m) {
    return this->getId() == m.getId();
}

ostream& operator<<(ostream &out, const Cliente& c) {
    out << "Nome - " << c.getName() << endl;
    out << "Idade - " << c.getAge() << endl;
    out << "Nif - " << c.getNif() << endl;
    return out;
}

ostream& operator<<(ostream &out, const Motorista &m) {
    out << "ID [" << m.getId() << "]" << endl;
    out << "Nome - " << m.getName() << endl;
    out << "Idade - " << m.getAge() << endl;
    out << "Salario - " << m.getSalario() << endl;
    out << "Horario - " << "[" << m.getHorario().first << " ; " << m.getHorario().second << "]" << endl;
    string s = "(";
    if (m.getCategorias().size() == 1) {
        s += m.getCategorias().at(0);
        s += ")";
    }
    else {
        for (size_t i = 0; i < m.getCategorias().size(); i++) {
            if (i == m.getCategorias().size() - 1) {
                s += m.getCategorias().at(i);
                s += ")";
            }
            else {
                s += m.getCategorias().at(i);
                s+= " ; ";
            }
        }
    }
    cout << "Categorias que conduz - " << s << endl;
    return out;
}

ClienteInexistente::ClienteInexistente(string nome, int nif) {
    this->name = nome;
    this->nif = nif;
}

int ClienteInexistente::getNif() const {return nif;}

string ClienteInexistente::getName() const {return name;}

ClienteRepetido::ClienteRepetido(string name, int age) {
    this->name = name;
    this->age = age;
}

string ClienteRepetido::getName() const {return name;}

int ClienteRepetido::getAge() const {return age;}

MotoristaInexistente::MotoristaInexistente(string name, int id) {
    this->name = name;
    this->id = id;
}

string MotoristaInexistente::getName() const {return name;}

int MotoristaInexistente::getId() const {return id;}

MotoristaRepetido::MotoristaRepetido(string name, int id) {
    this->name = name;
    this->id = id;
}

string MotoristaRepetido::getName() const {return name;}

int MotoristaRepetido::getId() const {return id;}
