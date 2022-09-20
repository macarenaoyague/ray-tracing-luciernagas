#include <iostream>
#include <cstdlib>
#include "Mundo.h"
#include <tuple>

// ffmpeg -framerate 4 -i p%2d.bmp -s:v 600x400 -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p movie.mp4

vec3 pa(6, 18, 2), pb(6, 2, 2);
float radioCilindroSmall = 6.5, radioCilindroBig = 7;
float l = radioCilindroSmall/(sqrt(2.0f);

vec3 centroRandom() {
    int radioCilindroSmallInt = (int)radioCilindroSmall;
    float z = (rand() % radioCilindroSmallInt) + pa.z;
    float x = sqrt(radioCilindroSmallInt*radioCilindroSmallInt - z*z) + pa.x;
    float y = (rand()% ((int)(pa.y - 1))) - pb.y + 1;
    return vec3(z, x, y);
}

vec3 colorLuciernaga(1, 0.74, 0.21);
vec3 colorAlien(0.53, 0.66, 0.97);

std::tuple<Esfera*, Luz*> generarLuciernaga(vec3*& centro) {
    Luz* luz = new Luz(centro, colorLuciernaga); 
    Esfera* luciernaga = new Esfera(colorLuciernaga, 0.9, 0.9, 30, 0, centro, radioLuz, luz);
    return std::make_tuple(luciernaga, luz);
}

vector<vec3*> centros = { new vec3(6, 4, 2), new vec3(6, 6.5, 2), new vec3(6, 9, 2), new vec3(6, 11.5, 2), new vec3(6, 14, 2), new vec3(-6, 14, 2) };

void generarLuciernagas(vector<Objeto*>& luciernagas, vector<Luz*>& luces) {
    for (int i = 0; i < centros.size(); i++) {
        auto [luciernaga, luz] = generarLuciernaga(centros[i]);
        luciernagas.push_back(luciernaga);
        luces.push_back(luz);
    }
    luces[centros.size()-1]->color = colorAlien;
    luciernagas[centros.size()-1]->color = colorAlien;
}

float randOffset() {
    float offset = float(rand()%100) / 100.0;
    int sign = rand()%2 == 0 ? 1 : -1;
    return sign*offset/2.0;
}

float x_min = pa.x-l, x_max = pb.x+l;
float y_min = pb.y, y_max = pa.y;
float z_min = pa.z+l, z_max = pb.z-l;

void moverLuciernagas(vector<Objeto*>& luciernagas, vector<Luz*>& luces) {
    float offset;
    for (int i = 0; i < centros.size(); i++) {
        offset = randOffset();
        if ((*centros[i]).x + offset < x_min || (*centros[i]).x + offset > x_max) (*centros[i]).x -= offset;
        else (*centros[i]).x += offset;
        offset = randOffset();
        if ((*centros[i]).y + offset < y_min || (*centros[i]).y + offset > y_max) (*centros[i]).y -= offset;
        else (*centros[i]).y += offset;
        offset = randOffset();
        if ((*centros[i]).z + offset < z_min || (*centros[i]).z + offset > z_max) (*centros[i]).z -= offset;  
        else (*centros[i]).z += offset;      
    }
}

void LuciernagasFrame(Camara& camara, vector<Objeto*> objetos, vector<Luz*> luces, int i) {
    // luz principal
    // luces.push_back(new Luz(new vec3(10, 30, 20), vec3(1, 1, 1)));

    // objetos.push_back(new Esfera(vec3(1, 1, 1), 0.9, 0.5, 40, 0, new vec3(4, 6, 7), 1)); 

    // esfera atrás descomentar
    objetos.push_back(new Esfera(vec3(1, 1, 1), 0.9, 0.1, 8, 0, new vec3(-5, 9, 2), 2)); 
    objetos.push_back(new Esfera(vec3(1, 1, 1), 0.1, 1, 32, 0, new vec3(-17, 6, -1), 2)); 
    objetos.push_back(new Esfera(vec3(1, 1, 1), 0.9, 0.5, 40, 0, new vec3(-10, 7, 5), 2)); 
    objetos.push_back(new Esfera(vec3(1, 1, 1), 0.9, 0.5, 40, 1, new vec3(-6.5, 2, 0), 2)); 

    objetos.push_back(new Esfera(vec3(1, 1, 1), 0.9, 0.5, 40, 1, new vec3(-10, 10, 6), 2)); 

    objetos.push_back(new Esfera(vec3(1, 1, 1), 0.9, 0.5, 40, 0, new vec3(18, 5, 5), 5)); 

    // tapa
    objetos.push_back(new Cilindro(vec3(1, 1, 1), 0.9, 0.1, 8, 0, vec3(6, 18, 2), vec3(6, 20, 2), radioCilindroBig+1));
    // envase
    objetos.push_back(new Cilindro(vec3(1, 1, 1), 0.9, 0.1, 30, 1, pa, pb, radioCilindroSmall));
    objetos.push_back(new Cilindro(vec3(1, 1, 1), 0.9, 0.1, 30, 1, pa, pb, radioCilindroBig));

    // piso
    objetos.push_back(new Plano(vec3(0.64, 0.16, 0.16), 0.7, 0, 10, 0, vec3(0, 1, 0), 2));

    Mundo mundo(camara, luces, objetos);
    mundo.Escenario(i);
}

vec3 eyeStart(3, 20, 80);

enum Tipo {
    zoomear,
    reloj,
    contrarreloj,
    deszoomear
};

void moverCamara(Camara& camara, Tipo op) {
    if (op == zoomear) {
        camara.eye.z -= 0.66;
    }
    
    else if (op == deszoomear) {
        camara.eye.z += 0.66;
    }
    
    else if (op == reloj) {
        camara.eye.x += 0.33; camara.eye.z -= 0.17;
    }
    
    else if (op == contrarreloj) {
        camara.eye.x -= 0.33; camara.eye.z += 0.17;
    } 

    camara.inicializar();
}

int main() {
    vec3 eye = eyeStart, center = vec3(0, 4, 0), up = vec3(0, 1, 0);
    float _near = 4, fov = 60, w = 600, h = 400;
    Camara camara(eye, center, up, _near, fov, w, h);

    vec3 posicionCilindro(0,0,0);
    vector<Objeto*> luciernagas; 
    vector<Luz*> lucesLuciernagas;

    generarLuciernagas(luciernagas, lucesLuciernagas);

    int fps = 10;
    int s = 30;
    int nFrames = fps * s;

    for (int i = 0; i < nFrames; i++) {
        LuciernagasFrame(camara, luciernagas, lucesLuciernagas, i);
        moverLuciernagas(luciernagas, lucesLuciernagas);
        if (i < nFrames*0.25) moverCamara(camara, zoomear); 
        else if (i < nFrames*0.40) {}
        else if (i < nFrames*0.55) moverCamara(camara, reloj);
        else if (i < nFrames*0.70) moverCamara(camara, contrarreloj);
        else if (i < nFrames*0.80) {}
        else moverCamara(camara, deszoomear);
    }

    return 0;
}
