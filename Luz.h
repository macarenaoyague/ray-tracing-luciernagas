#ifndef INC_20222_RAYTRACING_LUZ_H
#define INC_20222_RAYTRACING_LUZ_H

#include "vector.h"

class Luz {
public:
    vec3* pos;
    vec3 color;
    Luz(vec3* pos, vec3 color) 
    : pos(pos), color(color) {}
};


#endif //INC_20222_RAYTRACING_LUZ_H
