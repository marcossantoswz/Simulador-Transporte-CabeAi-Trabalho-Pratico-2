#include "../include/escalonador.h"

MinHeap::MinHeap(){
    this->tamanho_atual = 0;
    this->eventos = new Evento[1000];
}
MinHeap::~MinHeap(){
    delete[] this->eventos;
}
void MinHeap::troca(int i, int j){
    Evento temp = eventos[i];
    eventos[i] = eventos[j];
    eventos[j] = temp;
}
void MinHeap::heapify_up(int indice){
    if(indice == 0) return;
    //achando pai no array
    int indice_pai = (indice-1)/2;
    if(eventos[indice].hora < eventos[indice_pai].hora){
        troca(indice, indice_pai);
        heapify_up(indice_pai);
    }
}
void MinHeap::heapify_down(int indice){
    //calcula filhos
    int indice_filho_esq = (2*indice)+1;
    int indice_filho_dir = (2*indice)+2;

    int indice_menor = indice;

    //verifica o menor
    if(indice_filho_esq < tamanho_atual && eventos[indice_filho_esq].hora < eventos[indice_menor].hora){
        indice_menor = indice_filho_esq;
    }
    if(indice_filho_dir<tamanho_atual && eventos[indice_filho_dir].hora < eventos[indice_menor].hora){
        indice_menor = indice_filho_dir;
    }

    if(indice_menor != indice){
        troca(indice, indice_menor);
        heapify_down(indice_menor);
        //recursao para quando indice_menor = indice
    }
}
bool MinHeap::vazio(){
    if(tamanho_atual!=0) return 0;
    else return 1;
}
void MinHeap::InserirEvento(Evento e){
    eventos[tamanho_atual] = e;
    heapify_up(tamanho_atual);
    tamanho_atual++;
}
Evento MinHeap::RetirarProximoEvento(){
    if(tamanho_atual == 0);//cout << "Sem nada no min heap" << endl;
    Evento evento_retornar = eventos[0];
    eventos[0] = eventos[tamanho_atual-1];
    tamanho_atual--;
    heapify_down(0);
    return evento_retornar;
}
void MinHeap::finalizar(){

}