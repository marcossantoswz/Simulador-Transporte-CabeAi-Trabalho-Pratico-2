#include "../include/demanda.h"
#include <cmath>

Demanda::Demanda(){}

Demanda::~Demanda(){}

// Setter
void Demanda::setDemanda(int id, double tempo, double origem_x, double origem_y, double destino_x, double destino_y, int estado){
    this->id_demanda = id;
    this->distancia_individual = 0;
    this->tempo = tempo;
    this->origem_x = origem_x;
    this->origem_y = origem_y;
    this->destino_x = destino_x;
    this->destino_y = destino_y;
    this->estado = estado;
    calcularDistancia();
}

void Demanda::calcularDistancia(){
    double dx = this->origem_x - this->destino_x;
    double dy = this->origem_y - this->destino_y;
    this->distancia_individual = sqrt(pow(dx, 2) + pow(dy, 2));
}

// --- Getters ---
int Demanda::getId() const {
    return this->id_demanda;
}

double Demanda::getDistanciaIndividual() const{
    return this->distancia_individual;
}

double Demanda::getTempo() const {
    return this->tempo;
}

double Demanda::getOrigemX() const {
    return this->origem_x;
}

double Demanda::getOrigemY() const {
    return this->origem_y;
}

double Demanda::getDestinoX() const {
    return this->destino_x;
}

double Demanda::getDestinoY() const {
    return this->destino_y;
}

void Demanda::setEstado(int novo_estado) {
    this->estado = novo_estado;
}

int Demanda::getEstado() const{
    return this->estado;
}