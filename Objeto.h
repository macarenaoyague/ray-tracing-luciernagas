#ifndef INC_20222_RAYTRACING_OBJETO_H
#define INC_20222_RAYTRACING_OBJETO_H
#include "vector.h"
#include "Rayo.h"
#include "Luz.h"

class Objeto {

public:

    vec3 color;

    // kd: constante difusa
    // ks: constante especular
    // n: 
    // idr: indice de refraccion
    float kd, ks, n, idr;

    // es fuente de luz
    Luz* luz;

    Objeto(vec3 color, float kd, float ks, float n, float idr, Luz* luz) : color(color), kd(kd), ks(ks), n(n), idr(idr), luz(luz) {}
    Objeto(vec3 color, float kd, float ks, float n, float idr) : color(color), kd(kd), ks(ks), n(n), idr(idr) { luz = nullptr; }
    
    // rayo que bota la cámara
    virtual bool interseccion(Rayo &rayo, float &t, vec3 &normal) = 0;
};

class Esfera : public Objeto {

public:

    // centro de la esfera
    vec3* cen;
    float radio;

    Esfera(vec3 color, float kd, float ks, float n, float idr, vec3* cen, float radio) 
    : Objeto(color, kd, ks, n, idr), cen(cen), radio(radio) {
        luz = nullptr;
    };

    Esfera(vec3 color, float kd, float ks, float n, float idr, vec3* cen, float radio, Luz* luz) 
    : Objeto(color, kd, ks, n, idr, luz), cen(cen), radio(radio) {};
    
    bool interseccion(Rayo &rayo, float &t, vec3 &normal);
};

class Plano : public Objeto {

public:

    // es el "segundo punto", en sí indica la dirección 
    vec3 normal;
    // distancia al centro del mundo
    float d;

    Plano(vec3 color, float kd, float ks, float n, float idr, vec3 normal, float d)
    : Objeto(color, kd, ks, n, idr), normal(normal), d(d) {}

    bool interseccion(Rayo &rayo, float &t, vec3 &normal_s);
};

class Cilindro : public Objeto {

    public:

    // punto inicial y final que forman cilindro
    vec3 p_a, p_b;
    // radio
    float r;
    
    Cilindro(vec3 color, float kd, float ks, float n, float idr, vec3 p_a, vec3 p_b, float r) 
    : Objeto(color, kd, ks, n, idr), p_a(p_a), p_b(p_b), r(r) { }
    
    bool interseccion(Rayo &rayo, float &t, vec3 &normal);
};

#endif //INC_20222_RAYTRACING_OBJETO_H
