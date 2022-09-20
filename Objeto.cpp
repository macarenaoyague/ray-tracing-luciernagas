#include <cmath>
#include "Objeto.h"

bool Esfera :: interseccion(Rayo &rayo, float &t, vec3 &normal) {
    vec3 d = rayo.dir;
    // vector del origen al centro
    vec3 o_c = rayo.ori - (*cen);

    float a = d.punto(d);
    float b = 2 * d.punto(o_c);
    float c = o_c.punto(o_c) - radio*radio;

    float det = b*b - 4*a*c;
    // si det>0: 2 raíces diferentes
    // si det=0: 2 raíces iguales
    if (det >= 0) {
        // distancia de intersección (tiro un rayo y "entra y sale")
        float t1 = (-b - sqrt(det)) / (2*a);
        float t2 = (-b + sqrt(det)) / (2*a);
        // cojo la más cercana para la cámara (imagen 2d)
        t = std :: fmin(t1, t2);
        if (t <= 0) return false;
        // origen + distancia entre ambos puntos * dirección
        vec3 p_i = rayo.ori + t * rayo.dir;
        normal = p_i - (*cen);
        normal.normalize();
        return true;
    }
    return false;
}

bool Plano :: interseccion(Rayo &rayo, float &t, vec3 &normal_s) {
    t = -(normal.punto(rayo.ori) + d) / (normal.punto(rayo.dir));
    if (t > 0) {
        normal_s = normal;
        return true;
    }
    return false;
}

bool Cilindro :: interseccion(Rayo &rayo, float &t, vec3 &normal) {
    vec3 ca = p_b - p_a;
    vec3 oc = rayo.ori - p_a;
    float caca = ca.punto(ca);
    float card = ca.punto(rayo.dir);
    float caoc = ca.punto(oc);
    float a = caca - card*card;
    float b = caca * oc.punto(rayo.dir) - caoc*card;
    float c = caca * oc.punto(oc) - caoc*caoc - r*r*caca;
    float h = b*b - a*c;
    if( h < 0.0 ) return false; //no intersection
    h = sqrt(h);
    t = (- b - h)/a;
    if (t <= 0) return false;
    // body
    float y = caoc + t*card;
    if (y > 0.0 && y < caca ) {
        normal = (oc + t*rayo.dir - ca*y/caca) / r;
        normal.normalize();
        return true;
    }
    // caps
    t = (((y < 0.0) ? 0.0 : caca) - caoc) / card;
    if (t <= 0) return false;
    if (abs(b + a*t) < h) {
        normal =  ca * sgn(y) / caca;
        normal.normalize();
        return true;
    }
    return false; //no intersection
}