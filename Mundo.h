#ifndef INC_20222_RAYTRACING_MUNDO_H
#define INC_20222_RAYTRACING_MUNDO_H

#include "Camara.h"

class Mundo {

public:

    vector<Objeto*> objetos;
    vector<Luz*> luces;
    Camara camara;

    Mundo(Camara& camara, std::vector<Luz*>& luces, std::vector<Objeto*>& objetos) 
    : camara(camara), luces(luces), objetos(objetos) {}

    void Escenario(int i) {
        camara.renderizar(luces, objetos, i);
    }

};

#endif //INC_20222_RAYTRACING_MUNDO_H