//
// Created by caion on 05/11/2019.
//
#include <iostream>
#include "Empresa.h"
#include "Utils.h"
#include <fstream>
using namespace std;

vector <Cliente> Empresa::getClientes() const {return clientes;}

vector <Motorista> Empresa::getMotoristas() const {return motoristas;}

string Empresa::getName() const {return nome;}

void Empresa::setClientes(vector<Cliente> clientes) {
    this->clientes = clientes;
}

void Empresa::setMotoristas(vector<Motorista> motoristas) {
    this->motoristas = motoristas;
}

void Empresa::setServicos(vector<ServicoTransporte> st) {this->servicos = st;}

vector <ServicoTransporte> Empresa::getServicos() const {return servicos;}

map <pair<string,string>,double> Empresa::getDistancias() const {return distancias;}

Empresa::Empresa(string filename) {
    this->filename = filename;
    ifstream file;
    file.open(this->filename);
    if (file.is_open()){
        getline(file, nome);
        getline(file, clientes_ficheiro);
        getline(file, motoristas_ficheiro);
        getline(file, camioes_ficheiro);
        getline(file, distancias_ficheiro);
        getline(file, servicos_ficheiro);
    }
    file.close();
    readCamioes();
    readServicos();
    readClientes();
    readDistancias();
    readMotoristas();
    this->numCamioes = camioes.size();
    //sortCamioes();
}

void Empresa::readClientes() {
    vector <Cliente> result;
    ifstream file;
    file.open(this->clientes_ficheiro);
    if (file.is_open() && !file.eof()){
        while (true){
            string name, age_str, nif_str, packs_str,sep;
            getline(file, name);
            getline(file, age_str);
            getline(file, nif_str);
            getline(file, packs_str);
            Cliente* p = new Cliente(name, stoi(age_str), stoi(nif_str), servicesBuilder(packs_str, this->servicos));
            for (ServicoTransporte st: p->getServicos()) eliminarServico(st);//o servico deixa de estar diponivel para outros clientes
            this->clientes.push_back(*p);
            if (file.eof()) break;
            else getline(file, sep);
        }
    }
}

void Empresa::readCamioes() {
    ifstream file;
    file.open(this->camioes_ficheiro);
    if (file.is_open()){
        string numCamioes_str;
        getline(file, numCamioes_str);
        this->numCamioes = stoi(numCamioes_str);

        while (!file.eof()) {
            string s;
            char tipo;
            getline(file, s);
            tipo = s.at(0);
            switch (tipo) {
                case 'p': {
                    //camioes perigosos
                    string id_str, marca1, capacidade_str, nivel_str, km_str;
                    getline(file, id_str);
                    getline(file, marca1);
                    getline(file, capacidade_str);
                    getline(file, km_str);
                    getline(file, nivel_str);
                    Perigosos *p = new Perigosos(stoi(capacidade_str), marca1,stod(km_str), nivel_str);
                    Camiao* cap = p;
                    this->camioes.push_back(cap);
                    if (!file.eof()) {
                        string sep;
                        getline(file, sep);
                    }
                    break;
                }

                case 'c': {
                    //camioes com congelacao
                    string id_str, marca1, capacidade_str, temp_str, km_str;
                    getline(file, id_str);
                    getline(file, marca1);
                    getline(file, capacidade_str);
                    getline(file, km_str);
                    getline(file, temp_str);
                    Congelacao *c = new Congelacao(stoi(capacidade_str), marca1, stod(km_str), stoi(temp_str));
                    Camiao* cac = c;
                    this->camioes.push_back(cac);

                    //delete c;
                    if (!file.eof()) {
                        string sep;
                        getline(file, sep);
                    }
                    break;
                }

                case 'n': {
                    // camioes "normais"
                    string id_str, marca1, capacidade_str, temp_str, km_str;
                    getline(file, id_str);
                    getline(file, marca1);
                    getline(file, capacidade_str);
                    getline(file, km_str);
                    Normal *n = new Normal(stoi(capacidade_str), marca1, stod(km_str));
                    Camiao* can = n;
                    this->camioes.push_back(can);
                    if (!file.eof()) {
                        string sep;
                        getline(file, sep);
                    }
                    break;
                }

                case 'a': {
                    //camioes de transporte de animais
                    string id_str, marca1, capacidade_str, temp_str, num_anumais_str, km_str;
                    getline(file, id_str);
                    getline(file, marca1);
                    getline(file, capacidade_str);
                    getline(file, km_str);
                    getline(file, num_anumais_str);
                    Animais *a = new Animais(stoi(capacidade_str), marca1,stod(km_str), stoi(num_anumais_str));
                    Camiao* caa = a;
                    this->camioes.push_back(caa);
                    //delete caa;
                    if (!file.eof()) {
                        string sep;
                        getline(file, sep);
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
}

vector<Camiao *> Empresa::getCamioes() const {return camioes;}

std::set<string> Empresa::getLocalizacoes() const {return localizacoes;}

void Empresa::updateClientes() {
    ofstream file;
    string separator = ":::::";
    file.open(this->clientes_ficheiro);
    if (file.is_open()){
        for (Cliente c: clientes){
            file << c.getName() << endl;
            file << c.getAge() << endl;
            file << to_string(c.getNif()) << endl;
            file << to_string_id(c.getServicos());
            if (c.getNif() != clientes.at(clientes.size()-1).getNif()){
                file << endl << separator << endl;
            }
        }
    }
}

void Empresa::updateCamioes() {
    int ctr = 0;
    ofstream file;
    string separator = ":::::";
    string identificador;
    file.open(this->camioes_ficheiro);
    if (file.is_open()){
        file << this->numCamioes << endl;
        for (Camiao* c: camioes){
            Perigosos *np = dynamic_cast<Perigosos*>(c);
            Normal* nn = dynamic_cast<Normal*>(c);
            Animais* na = dynamic_cast<Animais*>(c);
            Congelacao* nc = dynamic_cast<Congelacao*>(c);
            if (np != nullptr){ //camiao perigoso
                identificador = "p";
                file << identificador << endl;
                file << np->getId() << endl;
                file << np->getMarca() << endl;
                file << np->getCapacidade() << endl;
                file << np->getKmPercorridos() << endl;
                file << np->getNivel();
                ctr++;
                if (ctr < this->numCamioes){
                    file << endl << separator << endl;
                }
            }

            else if (nn != nullptr){ //camiao normal
                identificador = "n";
                file << identificador << endl;
                file << nn->getId() << endl;
                file << nn->getMarca() << endl;
                file << nn->getCapacidade() << endl;
                file << nn->getKmPercorridos();
                ctr++;
                if (ctr < this->numCamioes){
                    file << endl << separator << endl;
                }
            }

            else if (na != nullptr){
                identificador = "a";
                file << identificador << endl;
                file << na->getId() << endl;
                file << na->getMarca() << endl;
                file << na->getCapacidade() << endl;
                file << na->getKmPercorridos() << endl;
                file << na->getNumAnimais();
                ctr++;
                if (ctr < this->numCamioes){
                    file << endl << separator << endl;
                }
            }

            else if (nc != nullptr){
                identificador = "c";
                file << identificador << endl;
                file << nc->getId() << endl;
                file << nc->getMarca() << endl;
                file << nc->getCapacidade() << endl;
                file << nc->getKmPercorridos() << endl;
                file << nc->getTempMin();
                ctr++;
                if (ctr < this->numCamioes){
                    file << endl << separator << endl;
                }
            }
        }
    }
    file.close();
}


void Empresa::readMotoristas() {
    ifstream file;
    file.open(this->motoristas_ficheiro);
    if (file.is_open() && !file.eof()) {
        while (true) {
            string name, age_str, salario_str, horario_str, categorias_str, sep;
            getline(file, name);
            getline(file, age_str);
            getline(file, salario_str);
            getline(file, horario_str);
            getline(file, categorias_str);
            Motorista *m = new Motorista(name, stoi(age_str), stoi(salario_str), toPair(horario_str), categoryVector(categorias_str));
            this->motoristas.push_back(*m);
            if (file.eof()) break;
            else getline(file, sep);
        }
    }
}

void Empresa::updateMotoristas() {
    ofstream file;
    string separator = ":::::";
    file.open(this->motoristas_ficheiro);
    int numMotoristas = motoristas.size();
    if (file.is_open()){
        for (Motorista m: motoristas){
            file << m.getName() << endl;
            file << to_string(m.getAge()) << endl;
            file << to_string(m.getSalario()) << endl;
            if (m.getHorario().first.length() == 4) file << "0" << m.getHorario().first << " -> " << m.getHorario().second << endl;
            else file << m.getHorario().first << " -> " << m.getHorario().second << endl;
            int numCategorias = m.getCategorias().size();
            if (numCategorias > 1) {
                int n = 1;
                while (n != numCategorias) {
                    file << m.getCategorias().at(n - 1) << " ; ";
                    n++;
                }
                file << m.getCategorias().at(n - 1);
            }
            else file << m.getCategorias().at(0);
            if (!(m == motoristas.at(numMotoristas - 1))){
                file << endl << separator << endl;
            }
        }
    }
}


void Empresa::readDistancias() {
    ifstream file;
   // map< pair<string, string>, double> res;
    file.open(this->distancias_ficheiro);
    if (file.is_open()){
        while(!file.eof()){
            string line;
            getline(file, line);
            pair <string, string> pair = distanceSplitter(line);
            line.erase(0, line.find("- ")+2);
            double d = stod(line);
            this->distancias[pair] = d;
            this->localizacoes.insert(pair.first);
            this->localizacoes.insert(pair.second);
        }
    }
    file.close();
}

void Empresa::adicionarCliente(Cliente novoCliente) {
    for (Cliente c: clientes){
        if (c == novoCliente)
            throw ClienteRepetido(novoCliente.getName(), novoCliente.getAge());
    }
    this->clientes.push_back(novoCliente);
}

void Empresa::eliminarCliente(Cliente cli) {
    size_t control = clientes.size();
    for (auto it = clientes.begin(); it != clientes.end(); it) {
        if (*it == cli) {
            for (ServicoTransporte st: it->getServicos()){
                if (getCurrentTime() < st.getDate())
                    setDisponivel(st);
            }
            cout << "Cliente eliminado: " << cli.getName() << endl;
            it = clientes.erase(it);
        }
        else it++;
    }
    if (control == clientes.size()) //vetor permanece intacto => nenhum cliente removido
        throw (ClienteInexistente(cli.getName(), cli.getNif()));
}

void Empresa::adicionarMotorista(Motorista mot) {
    for (Motorista m: motoristas)
        if (m == mot) throw MotoristaRepetido(mot.getName(), mot.getId());
    this->motoristas.push_back(mot);
}

void Empresa::eliminarMotorista(Motorista mot) {
    size_t control = motoristas.size();
    for (vector<Motorista>::iterator it = motoristas.begin(); it != motoristas.end(); it)
        if (*it == mot) {
            cout << "Motorista eliminado: " << mot.getName() << " (Id = " << mot.getId() << ")" << endl;
            it = motoristas.erase(it);
            atualizarServicosMotorista();
        }
        else it++;
    if (control == motoristas.size()) //vetor permanece intacto => nenhum motorista removido
        throw (MotoristaInexistente(mot.getName(), mot.getId()));
}


void Empresa::adicionarCamiao(Camiao *novoC) {
    for (Camiao* c: camioes){
        if (*c == *novoC)
            throw CamiaoRepetido(novoC->getMarca(), novoC->getId());
    }
    //novoC->setkmPercorridos(0);
    this->camioes.push_back(novoC);
    this->numCamioes++;
}

void Empresa::eliminarCamiao(Camiao *c) {
    size_t control = camioes.size();
    for (auto it = camioes.begin(); it != camioes.end(); it){
        if (**it == *c) {
            it = camioes.erase(it);
            this->numCamioes--;
            this->atualizarServicosCamiao(); // atualizar os servços que possuem este camiao
        }
        else it++;
    }

    if (control == camioes.size())
        throw(CamiaoInexistente(c->getId(), c->getMarca()));
}


//retornar apenas os camioes de um determinado tipo
vector<Camiao *> Empresa::getCamioesTipo(vector<Camiao *> camioes, string categoria){
    vector<Camiao *> res, result;
    switch(categoria.at(0)){
        case 'p':{ //camioes perigosos
            for (Camiao* c: camioes){
                Perigosos* np = dynamic_cast<Perigosos*>(c);
                if (np != nullptr)
                    res.push_back(c);
            }
        }

        case 'c':{ //camioes de congelacao
            for (Camiao* c: camioes){
                Congelacao* nc = dynamic_cast<Congelacao*>(c);
                if (nc != nullptr)
                    res.push_back(c);
            }
        }

        case 'n':{
            for (Camiao* c: camioes){
                Normal* nn = dynamic_cast<Normal*>(c);
                if (nn != nullptr)
                    res.push_back(c);
            }
        }

        case 'a':{
            for (Camiao* c: camioes){
                Animais* na = dynamic_cast<Animais*>(c);
                if (na != nullptr)
                    res.push_back(c);
            }
        }
    }

    for (Camiao* c: res){
        for (Camiao* c1: this->camioes){
            if (*c == *c1)
                result.push_back(c);
        }
    }

    return result;
}



void Empresa::readServicos() {
    ifstream file;
    string separator;
    file.open(this->servicos_ficheiro);
    if (file.is_open()) {
        while (true) {
            string id_str, tipo, id_camioes_str, origem, destino, horario, date_str, b;
            getline(file, id_str);
            getline(file, tipo);
            getline(file, id_camioes_str);
            getline(file, origem);
            getline(file, destino);
            getline(file, horario);
            getline(file, date_str);
            getline(file, b);
            ServicoTransporte n(ServicoTransporte::globalID, origem, destino, tipo,camioesBuilder(id_camioes_str, this->camioes,tipo), horario, dateSplitter(date_str),(unsigned) stoi(b));
            this->servicos.push_back(n);
            ServicoTransporte::globalID++;
            if (file.eof())
                break;
            getline(file, separator);
        }
    }

    for (ServicoTransporte st:this->servicos) {
        if (st.getDate() < getCurrentTime())// || st.getCamioes().size() == 0)
            eliminarServico(st); // elimina servico do cliente se este ja tiver ocorrido
    }
}

void Empresa::updateServicos() {
    ofstream file;
    string separator = ":::::";
    file.open(this->servicos_ficheiro);
    if (file.is_open()){
        for (ServicoTransporte st: servicos){
            file << st.getId() << endl;
            file << st.getTipo() << endl;
            file << to_string_camioes(st.getCamioes()) << endl;
            file << st.getOrigem() << endl;
            file << st.getDestino() << endl;
            if (st.getHorario().length() == 4) file << "0" << st.getHorario() << endl;
            else file << st.getHorario() << endl;
            file << toStringDate(st.getDate()) << endl;
            file << st.getDisponibilidade();
            if (!(st == servicos.at(servicos.size()-1))) //verifica se é o ultimo elemento do vetor
                file << endl << separator << endl;
        }
    }
}


void Empresa::atualizarServicosCamiao() {
    for (auto it = this->servicos.begin(); it != this->servicos.end(); it++){
        vector <Camiao *> Ncamioes;
        for (Camiao* c: it->getCamioes()){
            for (Camiao *c1: camioes){
                if (*c == *c1)
                    Ncamioes.push_back(c);
            }
        }
        it->setCamioes(Ncamioes);

    }
    cout << "Servicos atualizados" << endl;
}

void Empresa::atualizarServicosMotorista() {
    for (vector<ServicoTransporte>::iterator it = servicos.begin(); it != servicos.end(); it) {
        bool MotoristaDisponivel = false;
        vector <Motorista> Nmotoristas;
        for (Motorista m: motoristas) {
            auto ite = find(m.getCategorias().begin(), m.getCategorias().end(), it->getTipo().at(0));
            if (m.isWorking(it->getHorario()) && ite != m.getCategorias().end()) {
                MotoristaDisponivel = true;
            }
        }
        if (MotoristaDisponivel) (*it).setDisponibilidade(0);
        else it++;
    }
}

vector<Camiao*> Empresa::sortCamioes() {
    vector<Camiao *> res = camioes;
    sort(res.begin(), res.end(),[](Camiao* a, Camiao *b){
        return a->getKmPercorridos() < b->getKmPercorridos();
    });
    return res;
}


void Empresa::adicionarServico(ServicoTransporte st) {
    bool MotoristasIndisponiveisctr = true;
    vector <Camiao *> Ncamioes;
    if (st.getCamioes().size() == 0) //verifica se existem camioes disponiveis para a entrega
        throw CamioesIndisponiveis();

    //verifica se as localizacoes são válidas
    auto i_origem = find(localizacoes.begin(), localizacoes.end(), st.getOrigem());
    auto i_destino = find(localizacoes.begin(), localizacoes.end(), st.getDestino());
    if (i_origem == localizacoes.end())
        throw LocalizacaoIndisponivel(st.getOrigem());
    else if (i_destino == localizacoes.end())
        throw LocalizacaoIndisponivel(st.getDestino());

    for (Motorista m: motoristas){
        vector<char> cate = m.getCategorias();
        sort(cate.begin(), cate.end());
        int idx = BinarySearch(cate, st.getTipo().at(0));
        if (m.isWorking(st.getHorario()) && idx != -1){
            MotoristasIndisponiveisctr = false;
        }
    }

    if (MotoristasIndisponiveisctr)
        throw MotoristasIndisponiveis(st.getOrigem(), st.getDestino());

    for (Camiao* c: st.getCamioes()){
        double km = c->getKmPercorridos();
        km += st.getDistancia(distancias);
        c->setkmPercorridos(km);
    }
    this->servicos.push_back(st);
}


void Empresa::eliminarServico(ServicoTransporte st) {
    bool camiaoEliminado = false;
    for (auto it = servicos.begin(); it != servicos.end(); it++){
        if (*it == st) {
            it->setDisponibilidade(0);
            camiaoEliminado = true;
        }
    }
    if (!camiaoEliminado) throw (ServicoInexistente(st.getOrigem(), st.getDestino()));
}

void Empresa::setCamioes(vector<Camiao *> camioes) {this->camioes = camioes;}

double Empresa::calcularLucroMensal() { //associado ao mes presente no tempo real
    double result = 0;
    for (Cliente c: clientes){
        for(ServicoTransporte st: c.getServicos())
            if (getCurrentTime().ano == st.getDate().ano && getCurrentTime().mes == st.getDate().mes && st.getDisponibilidade() == 0)
                result += st.getPreco(this->distancias);
    }
    for (Motorista m: motoristas){
        result -= m.getSalario();
    }
    return result;
}
/*
vector< pair<ServicoTransporte, int>> Empresa::EstatisticasServicos() {
    vector< pair<ServicoTransporte, int>> res;
    for (ServicoTransporte st: servicos){
        //pair <ServicoTransporte, int> p;
        int total=0;
        for (Cliente x: clientes){
            auto it = find(x.getServicos().begin(), x.getServicos().end(), st);
            if (it != x.getServicos().end()) total++;
        }
        pair <ServicoTransporte, int> p(st, total);
        res.push_back(p);
    }
    sort(res.begin(), res.end(), [](pair<ServicoTransporte, int> a, pair<ServicoTransporte, int> b){
        return a.second < b.second;
    });
    for (auto it = res.begin(); it != res.end(); it++)
        cout << it->first << "Adquirido por " << it->second << " clientes\n";
    return res;
}*/

bool Empresa::isAvailable(Camiao* ca, ServicoTransporte st){
    for (ServicoTransporte ser: servicos){
        auto it = find(ser.getCamioes().begin(), ser.getCamioes().end(), ca);
        if (it != ser.getCamioes().end()) {//camiao pertence a outro servico
            if (ser.getDate() == st.getDate() && ser.getHorario() == ser.getHorario())
                return false; //camiao indisponivel
        }
    }
    return true; // camiao disponivel
}

vector <ServicoTransporte> Empresa::servicosDisponiveis() {
    vector <ServicoTransporte> result;
    for (ServicoTransporte st: servicos){
        if (st.getDisponibilidade() == 1) result.push_back(st);
    }
    return result;
}

void Empresa::setDisponivel(ServicoTransporte st) {
    for (auto it = servicos.begin(); it != servicos.end(); it++){
        if (*it == st && getCurrentTime() < st.getDate() && st.getCamioes().size() > 0) it->setDisponibilidade(1);
    }
}