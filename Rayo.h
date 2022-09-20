#ifndef RAYCASTINGV2_RAYO_H
#define RAYCASTINGV2_RAYO_H

#include "vector.h"

class Rayo {
public:
    // ori es el origen del rayo (de la cámara)
    vec3 ori;
    vec3 dir;

    Rayo() {}
    Rayo(vec3 ori, vec3 dir) 
    : ori(ori), dir(dir) {};
};

#endif //RAYCASTINGV2_RAYO_H
