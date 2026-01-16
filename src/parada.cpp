#include "../include/parada.h"


Parada::Parada(){}

Parada::~Parada(){}

void Parada::setParada(double x, double y, bool embarque, int demanda_id) {
    this->coordenada_x = x;
    this->coordenada_y = y;
    this->is_embarque = embarque;
    this->id_demanda = demanda_id;
}

double Parada::getX() const {
    return this->coordenada_x;
}

double Parada::getY() const {
    return this->coordenada_y;
}

bool Parada::isEmbarque() const {
    return this->is_embarque;
}