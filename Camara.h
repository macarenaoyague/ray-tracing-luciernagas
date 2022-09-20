#ifndef INC_20222_RAYTRACING_CAMARA_H
#define INC_20222_RAYTRACING_CAMARA_H

#include <cmath>
#include "vector.h"
#include "CImg.h"
#include "Objeto.h"
#include "Luz.h"

#include <vector>
using namespace std;

using namespace cimg_library;
typedef unsigned char BYTE;
const float radioLuz = 1;

class Camara {

private:

    Objeto* buscar_objeto_intersectando(vector<Objeto*>& objetos, Rayo& rayo, vec3& p_i, vec3& N, Objeto* luzIntersectada);
    bool buscar_sombra(vector<Objeto*>& objetos, Rayo& rayo_sombra);
    vec3 calcular_color(vector<Objeto*>& objetos, vector<Luz*>& luces, Rayo& rayo, int profundidad, Objeto* luzIntersectada);
    void pintar_pixel(int x, int y, vec3& color);
    void fresnel(vec3 I, vec3 N, float &ior, float &kr);
    vec3 refract(vec3 I, vec3 N, float ior);
    

public:
    // eye: centro de la cámara (coordenada de la cámara)
    // center: hacia a donde apunta (ej: el ojo apuntando)
    // up: inclinación de la cámara (ej: mover la cabeza)
    vec3 eye, center, up;

    // _near: distancia a la ventana
    // resolución w x h
    // fov: el ángulo de visión (por ejemplo el fish eye)
    float fov, w, h, _near;

    float f, a, b;
    vec3 xe, ye, ze;
    CImg<BYTE> *pImg;

    void inicializar() {
        f = _near;
        // pasa el ángulo en radianes
        // * PI/180
        // a: el alto reak que sale del near 
        // tan = opuesto (que es a/2) / adyacente (near)
        // calculas con el ángulo la mitad de arriba
        a = 2 * f * tan(fov*M_PI/180 /2);
        // b: el ancho real
        // w/h = b/a
        b = w / h * a;

        ze = eye - center;
        ze.normalize();

        xe = up.cruz(ze);
        xe.normalize();
        
        ye = ze.cruz(xe);
    }

    Camara( vec3 eye, vec3 center, vec3 up, 
            float _near, float fov, float w, float h) :
            eye(eye), center(center), up(up),
            _near(_near), fov(fov), w(w), h(h) {
        inicializar();
    }

    void renderizar(vector<Luz*>& luces, vector<Objeto*>& objetos, int i);
};

#endif //INC_20222_RAYTRACING_CAMARA_H