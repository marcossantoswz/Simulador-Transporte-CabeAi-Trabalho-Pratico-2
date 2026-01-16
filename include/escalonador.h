#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include <iostream>
#include "corrida.h"

using namespace std;

struct Evento{
    double hora;
    bool isEmbarque;
    Corrida *corrida;
};
class MinHeap{
    private:
        Evento *eventos;
        int tamanho_atual;
    
        void heapify_up(int indice);
        void heapify_down(int indice);
        void troca(int i, int j);

    public:
        MinHeap();
        ~MinHeap();
        bool vazio();
        void InserirEvento(Evento e);
        Evento RetirarProximoEvento();
        void finalizar();
};

#endif