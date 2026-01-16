#ifndef DEMANDA_H
#define DEMANDA_H

class Demanda{
private:
    int id_demanda;
    double distancia_individual;
    double tempo; //horario que foi solicitada
    double origem_x;
    double origem_y;
    double destino_x;
    double destino_y;
    int estado; // 1. Corrida demandada
                // 2. Corrida individual
                // 3. Corrida combinada
                // 4. Corrida concluída

public:
    Demanda();
    ~Demanda();


    void setDemanda(int id, double tempo, double origem_x, double origem_y, double destino_x, double destino_y, int estado);
    void calcularDistancia();
    void setEstado(int novo_estado);

    int getId() const;
    double getTempo() const;
    double getDistanciaIndividual() const;
    double getOrigemX() const;
    double getOrigemY() const;
    double getDestinoX() const;
    double getDestinoY() const;
    int getEstado() const;
};

#endif