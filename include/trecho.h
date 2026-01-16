#ifndef TRECHO_H
#define TRECHO_H

#include "parada.h"
#include <string>
#include <cmath>

using namespace std;

class Trecho{
    private:
        Parada *origem;   
        Parada *destino; 
        double tempo;
        double distancia;
        string natureza; 
        
        void calcularDistancia();
        void definirNatureza();

    public:
        Trecho();
        ~Trecho();

        void setTrecho(Parada *p_origem, Parada *p_destino, double velocidade);

        double getDistancia() const;
        double getTempo() const;
        string getNatureza() const;
};

#endif