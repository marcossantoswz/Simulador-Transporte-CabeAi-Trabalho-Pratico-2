#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../include/corrida.h"
#include "../include/demanda.h"
#include "../include/escalonador.h"
#include "../include/parada.h"
#include "../include/trecho.h"

using namespace std;

void setDemandas(int num_demandas, Corrida *corridas, Demanda *demandas, ifstream &arquivo, double velocidade);
int criarCorridas(Demanda *demandas, Corrida *corridas, int num_demandas, int capacidade_veiculo, double max_intervalo, double max_distancia_origem,
    double max_distancia_destino, double eficiencia_min, double velocidade);
void inicializarEscalonador(MinHeap *minHeap, int num_demandas, Corrida *corridas);
void rodarSimulacao(MinHeap *minHeap);
double calcularDistancia(double x1, double x2, double y1, double y2);
double calcularEficiencia(Demanda demanda1, Demanda demanda2);


int main(int argc, char *argv[]) {

    int capacidade_veiculo, num_demandas;
    double velocidade, max_intervalo, max_distancia_origem,
    max_distancia_destino, eficiencia_min;

    // agora lê do teclado
    cin >> capacidade_veiculo >> velocidade >> max_intervalo >> max_distancia_origem
        >> max_distancia_destino >> eficiencia_min >> num_demandas;

    Demanda *demandas = new Demanda[num_demandas];
    MinHeap *minHeap = new MinHeap;
    Corrida *corridas = new Corrida[num_demandas];
    
    // substitui "arquivo" por "cin"
    for(int i=0; i<num_demandas; i++){
        int id;
        double origem_x, origem_y, destino_x, destino_y, tempo;
        cin >> id >> tempo >> origem_x >> origem_y >> destino_x >> destino_y;
        demandas[i].setDemanda(id, tempo, origem_x, origem_y, destino_x, destino_y, 1);
    }
    //setDemandas(num_demandas, corridas, demandas, cin, velocidade);

    int num_corridas = criarCorridas(
        demandas, corridas, num_demandas,
        capacidade_veiculo, max_intervalo, max_distancia_origem,
        max_distancia_destino, eficiencia_min, velocidade
    );

    inicializarEscalonador(minHeap, num_corridas, corridas);
    rodarSimulacao(minHeap);
    
    delete[] demandas;
    delete[] corridas;
    delete minHeap;

    return 0;
}



//void setDemandas(int num_demandas, Corrida *corridas, Demanda *demandas, ifstream &arquivo, double velocidade){
//    for(int i=0; i<num_demandas; i++){
 //      
 //       arquivo >> id >> tempo >> origem_x >> origem_y >> destino_x >> destino_y;
        
 //       demandas[i].setDemanda(id, tempo, origem_x, origem_y, destino_x, destino_y, 1);//1 = estado "demandada"

 //   }
//}

int criarCorridas(Demanda *demandas, Corrida *corridas,
    int num_demandas, int capacidade_veiculo,
    double max_intervalo, double max_distancia_origem,
    double max_distancia_destino, double eficiencia_min,
    double velocidade)
{
    int num_corridas_finais = 0;
    Corrida corridas_copia[100];
    
    for(int i=0; i<num_demandas; i++){
        
        //pula demanda demanda se ela já foi processada
        if(demandas[i].getEstado() != 1){
            continue; 
        }

        //se corrida ir for nova, inicializa ela
        corridas[num_corridas_finais].inicializarCorridaIndividual(&demandas[i], velocidade);
        demandas[i].setEstado(2);//individual no primeiro momento

        //percorre as demandas procurando pela demanda 'j' para juntar com a demanda 'i'
        for(int j=i+1; j<num_demandas; j++){
            
            if(demandas[j].getEstado() != 1) {
                continue;
            }

            if (corridas[num_corridas_finais].getNumDemandas() >= capacidade_veiculo) {
                break;
            }
            
            double diferenca_intervalo = fabs((demandas[j].getTempo() - demandas[i].getTempo()));
            if(diferenca_intervalo >= max_intervalo){
                continue;
            }

            //testa distancia das origens
            if(calcularDistancia(demandas[i].getOrigemX(), demandas[j].getOrigemX(), demandas[i].getOrigemY(), demandas[j].getOrigemY()) >= max_distancia_origem){
                break; 
            }
            
            //testa distancia dos destinos
            if(calcularDistancia(demandas[i].getDestinoX(), demandas[j].getDestinoX(), demandas[i].getDestinoY(), demandas[j].getDestinoY()) >= max_distancia_destino){
                break;
            }

            //corrida temporaria
            Corrida corrida_teste = corridas[num_corridas_finais];
            corrida_teste.adicionarDemanda(&demandas[j], velocidade);
            double eficiencia_calculada = corrida_teste.getEficiencia();

            //teste da eficiencia
            if (eficiencia_calculada > eficiencia_min) {
                corridas[num_corridas_finais] = corrida_teste; 
                demandas[j].setEstado(3); //marca 'j' como combinada
                demandas[i].setEstado(3); //marca 'i' como combinada
                

            } else {
                break;
            }
        }

        num_corridas_finais++;

    }
    
    return num_corridas_finais; 
}

double calcularDistancia(double x1, double x2, double y1, double y2){
    double dx = x1 - x2;
    double dy = y1 - y2;
    return sqrt(pow(dx, 2) + pow(dy, 2));
}

void inicializarEscalonador(MinHeap *minHeap, int num_corridas, Corrida *corridas) {
    for (int i = 0; i < num_corridas; i++) {
        //criando embarque de cada corrida
        Evento e;
        e.hora = corridas[i].getTempoSolicitacao();
        e.isEmbarque = 1;
        e.corrida = &corridas[i];
        
        minHeap->InserirEvento(e);
    }
}


void rodarSimulacao(MinHeap *minHeap) {
    while (!minHeap->vazio()) {
        //pega o evento de menor hora
        Evento eventoAtual = minHeap->RetirarProximoEvento();
        double relogio = eventoAtual.hora; //seta o relogio com o tempo atual
        Corrida* corridaAtual = eventoAtual.corrida;
        

        if (eventoAtual.isEmbarque==true){
            Evento eventoDesembarque;
            
            //calcule o tempo de desembarque
            double duracao = corridaAtual->getDuracao();
            eventoDesembarque.hora = relogio + duracao;
            eventoDesembarque.isEmbarque = false; //tipo desembarque
            eventoDesembarque.corrida = corridaAtual;
            
            //insirindo novo evento e ordena com metodos do escalonador
            minHeap->InserirEvento(eventoDesembarque);
            
        } else if (eventoAtual.isEmbarque == false) {

            //atualiza demanda para concluida
            corridaAtual->getDemanda()->setEstado(4);//4 = concluída
            
            //imprime estastisticas das corridas
            cout << fixed << setprecision(2) << relogio << " "
            << corridaAtual->getDistancia() << " " 
            << corridaAtual->getNumParadas() << " "; 
            corridaAtual->imprimirParadas();
            cout << endl;
        }
    }
}