#ifndef PARADA_H
#define PARADA_H

class Parada{
    private:
        int id_demanda;
        double coordenada_x;
        double coordenada_y;
        bool is_embarque; //true = embarque, false = desembarque

    public:
        Parada();
        ~Parada();

        void setParada(double x, double y, bool embarque, int demanda_id);

        double getX() const;
        double getY() const;
        bool isEmbarque() const;
};

#endif