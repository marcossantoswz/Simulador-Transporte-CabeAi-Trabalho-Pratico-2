#ifndef CORRIDA_H
#define CORRIDA_H

#include <string>
#include "trecho.h"
#include "parada.h"
#include "demanda.h"

class Corrida{
    private:
        Demanda *demandas[100];
        Trecho trechos[100];
        Parada paradas[100];

        int num_demandas;
        int num_trechos;
        int num_paradas;

        double duracao;
        double distancia;
        double eficiencia;

    public:
        Corrida();
        ~Corrida();

        void inicializarCorridaIndividual(Demanda *p_demanda, double velocidade);
        void adicionarDemanda(Demanda *demanda, double velocidade);
        void juntarCorrida(Demanda demanda);
        double calcularEficiencia();

        int getNumDemandas() const;
        double getTempoSolicitacao() const;
        double getDuracao() const;
        double getDistancia() const;
        double calcularDistanciaTotal();
        int getNumParadas() const;
        double getEficiencia() const;
        Demanda *getDemanda() const; 
        void imprimirParadas() const;
};

#endif