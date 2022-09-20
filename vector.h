#ifndef INC_20222_RAYTRACING_VECTOR_H
#define INC_20222_RAYTRACING_VECTOR_H

#include <cmath>

class vec3 {

public:

    float x, y, z;

    vec3() { 
        x = y = z =  0; 
    }

    vec3(float x, float y, float z)
    : x(x), y(y), z(z) {}

    vec3 operator+(vec3 v) { 
        return vec3(x+v.x, y+v.y, z+v.z); 
    }

    vec3 operator*(vec3 v) { 
        return vec3(x*v.x, y*v.y, z*v.z); 
    }

    vec3 operator/(vec3 v) { 
        if (v.x == 0 || v.y == 0 || v.z == 0) {
            throw "División entre 0";
        }
        return vec3(x/v.x, y/v.y, z/v.z); 
    }

    vec3 operator*(float f) { 
        return vec3(x*f, y*f, z*f); 
    }

    vec3 cruz(vec3 v) {
        return vec3(y*v.z - z*v.y,
                    z*v.x - x*v.z,
                    x*v.y - y*v.x);
    }

    float punto(vec3 v){
        return x*v.x + y*v.y + z*v.z;
    }

    void normalize(){
        double m = modulo();
        x = x/m;
        y = y/m;
        z = z/m;
    }

    double modulo() {
        return sqrt(x*x + y*y + z*z);
    }

    // para los colores
    void max_to_one(){
        float max_value = std::fmax(x, std::fmax(y,z));
        if (max_value > 1.0) {
            sqrt(x);
            sqrt(y);
            sqrt(z);
            x = x / max_value;
            y = y / max_value;
            z = z / max_value;
        }
    }
    
    vec3 operator-(vec3 v){
        return vec3(x-v.x, y-v.y,z-v.z);
    }
};

template <typename T> 
int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

vec3 operator/(float f, vec3 v);
vec3 operator/(vec3 v, float f);
vec3 operator*(float f, vec3 v);
vec3 operator-(vec3 v);
vec3 abs(vec3 &v);
vec3 sign(vec3 &v);
vec3 step(vec3 v1, vec3 v2);
float clamp(float menor, float mayor, float valor);

#endif //INC_20222_RAYTRACING_VECTOR_H