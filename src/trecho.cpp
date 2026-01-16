#include "../include/trecho.h"
#include <cmath>

Trecho::Trecho(){
    this->origem = nullptr;
    this->destino = nullptr;
    this->tempo = 0;
    this->distancia = 0;
    this->natureza = "";
}

Trecho::~Trecho(){}

//conferir se ta certo demais, disntancia euclideana
void Trecho::calcularDistancia() {
    double dx = this->destino->getX() - this->origem->getX();
    double dy = this->destino->getY() - this->origem->getY();
    this->distancia = sqrt(pow(dx, 2) + pow(dy, 2));
}

void Trecho::definirNatureza() {
    if (this->origem->isEmbarque() && this->destino->isEmbarque()) {
        this->natureza = "coleta";
    } else if (!this->origem->isEmbarque() && !this->destino->isEmbarque()) {
        this->natureza = "entrega";
    } else { //um embarque e um desembarque
        this->natureza = "deslocamento";
    }
}

void Trecho::setTrecho(Parada *p_origem, Parada *p_destino, double velocidade) {
    //ponteiros para paradas
    this->origem = p_origem;
    this->destino = p_destino;

    calcularDistancia();

    this->tempo = this->distancia / velocidade;

    definirNatureza();
}

double Trecho::getDistancia() const {
    return this->distancia;
}

double Trecho::getTempo() const {
    return this->tempo;
}

string Trecho::getNatureza() const{
    return this->natureza;
}