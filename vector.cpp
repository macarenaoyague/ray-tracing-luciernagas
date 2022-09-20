#include "vector.h"

vec3 operator/(float f, vec3 v) {
    if (v.x == 0 || v.y == 0 || v.z == 0) {
        throw "División entre 0";
    }
    float tx = f/v.x;
    float ty = f/v.y;
    float tz = f/v.z;
    return vec3(tx, ty, tz);
}

vec3 operator/(vec3 v, float f) {
    if (f == 0) {
        throw "División entre 0";
    }
    float tx = v.x/f;
    float ty = v.y/f;
    float tz = v.z/f;
    return vec3(tx, ty, tz);
}

vec3 operator*(float f, vec3 v) {
    return vec3(f*v.x, f*v.y, f*v.z);
}

vec3 operator-(vec3 v) {
    return vec3(-v.x, -v.y, -v.z);
}

vec3 abs(vec3 &v) {
    return vec3(abs(v.x), abs(v.y), abs(v.z));
}

vec3 sign(vec3 v) {
    return vec3(sgn(v.x), sgn(v.y), abs(v.z));
}

vec3 step(vec3 v1, vec3 v2) {
    return vec3(v2.x < v1.x ? 0 : 1,
                v2.y < v1.y ? 0 : 1,
                v2.z < v1.z ? 0 : 1);
}

float clamp(float menor, float mayor, float valor) {
    if (valor < menor) {
        return menor;
    }
    if (valor > mayor) {
        return mayor;
    }
    return valor;
}