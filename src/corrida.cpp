#include "../include/corrida.h"

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

Corrida::Corrida(){
    this->num_demandas = 0;
    this->num_trechos = 0;
    this->num_paradas = 0;
    this->duracao = 0;
    this->distancia = 0;
    this->eficiencia = 0;
}

Corrida::~Corrida(){
}

void Corrida::inicializarCorridaIndividual(Demanda *p_demanda, double velocidade) {
    this->demandas[0] = p_demanda;
    this->num_demandas = 1;

    this->paradas[0].setParada(p_demanda->getOrigemX(), p_demanda->getOrigemY(), true, p_demanda->getId()); //parada embarque
    this->paradas[1].setParada(p_demanda->getDestinoX(), p_demanda->getDestinoY(), false, p_demanda->getId());//parada desembarque
    this->num_paradas = 2;

    //O primeiro trecho sempre tem indice 0
    this->trechos[0].setTrecho(&this->paradas[0], &this->paradas[1], velocidade);
    this->num_trechos = 1;

    this->distancia = this->trechos[0].getDistancia();
    this->duracao   = this->trechos[0].getTempo();
    this->eficiencia = 1.0;
}

void Corrida::adicionarDemanda(Demanda *demanda, double velocidade) {

    int N = this->num_demandas; 
    this->demandas[N] = demanda;
    
    //reorganiza as paradas ao adicionar uma nova demanda na corrida
    for (int i = (N * 2) - 1; i >= N; i--) {
        this->paradas[i + 1] = this->paradas[i];
    }

    //insere nova parada de embarque
    this->paradas[N].setParada(demanda->getOrigemX(), demanda->getOrigemY(), true, demanda->getId());

    //insere o nova parada de desembarque na ultima posicao
    this->paradas[(N * 2) + 1].setParada(demanda->getDestinoX(), demanda->getDestinoY(), false, demanda->getId());

    this->num_demandas++;
    this->num_paradas += 2;

    //recalcula todos os trechos
    this->num_trechos = 0; 
    this->distancia = 0.0;
    this->duracao = 0.0;
    for(int i = 0; i < this->num_paradas - 1; i++){
        this->trechos[i].setTrecho(&this->paradas[i], &this->paradas[i+1], velocidade);
        this->num_trechos++;
        
        this->distancia += this->trechos[i].getDistancia();
        this->duracao += this->trechos[i].getTempo();
    }

    this->eficiencia = this->calcularEficiencia();
}

double Corrida::calcularDistanciaTotal(){
    double dist_total = 0;
    for(int i=0; i<this->num_trechos; i++){
        dist_total += this->trechos[i].getDistancia();
    }
    return dist_total;
}

double Corrida::calcularEficiencia() {
    if (this->num_demandas == 1) {
        return 1.0; 
    }

    double soma_distancias_individuais = 0.0;

    for (int i = 0; i < this->num_demandas; i++) {
        soma_distancias_individuais += this->demandas[i]->getDistanciaIndividual(); 
    }

    if (this->distancia == 0) {
        return 0; 
    }
    
    //eficiencia = soma dos trechos individuais / distancia total ?
    this->eficiencia = soma_distancias_individuais / this->distancia;
    return this->eficiencia;
}

double Corrida::getTempoSolicitacao() const {
    return this->demandas[0]->getTempo();
}

double Corrida::getDuracao() const {
    return this->duracao;
}

double Corrida::getDistancia() const {
    return this->distancia;
}
int Corrida::getNumDemandas() const{
    return this->num_demandas;
}

int Corrida::getNumParadas() const {
    return this->num_paradas;
}

double Corrida::getEficiencia() const{
    return this->eficiencia;
}

Demanda *Corrida::getDemanda() const {
    return this->demandas[0];
}

void Corrida::imprimirParadas() const {
    for (int i = 0; i < this->num_paradas; i++) {
        cout << fixed << setprecision(2) << "" << this->paradas[i].getX() << " " << this->paradas[i].getY();
        if (i < this->num_paradas - 1) {
            cout << " ";
        }
    }
}