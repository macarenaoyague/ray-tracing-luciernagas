#include "Camara.h"
#include <omp.h>
#include <string>

vec3 fondo = vec3(0, 0, 0);

void Camara :: renderizar(vector<Luz*>& luces, vector<Objeto*>& objetos, int i) {
    pImg = new CImg<BYTE>(w, h, 1, 3);
    // CImgDisplay dis_img((*pImg), "RayCasting");

    int x, y;

    // Para cada pixel lanzar un rayo
    #pragma omp parallel for private(x, y)
    {
    for (x = 0; x < w; x++) {
        for (y = 0; y < h; y++) {
            Rayo rayo;
            rayo.ori = eye;
            rayo.dir = -f*ze + a*(y/h - 0.5)*ye + b*(x/w - 0.5)*xe;
            rayo.dir.normalize();
            vec3 color = calcular_color(objetos, luces, rayo, 1, nullptr);
            pintar_pixel(x, y, color);
        }
    }
    }
    
    // dis_img.render((*pImg));
    // dis_img.paint();
    std::string name = "./pixeles/p";

    if (i < 10) name += "0";
    name += std::to_string(i) + ".bmp";
    pImg->save(name.c_str());
    // while (!dis_img.is_closed()) {
    //    dis_img.wait();
    // }
    delete pImg;
}

void Camara :: pintar_pixel(int x, int y, vec3& color) {
    (*pImg)(x, h-1-y, 0) = (BYTE)(color.x * 255);
    (*pImg)(x, h-1-y, 1) = (BYTE)(color.y * 255);
    (*pImg)(x, h-1-y, 2) = (BYTE)(color.z * 255);
}

Objeto* Camara :: buscar_objeto_intersectando(vector<Objeto*>& objetos, Rayo& rayo, vec3& p_i, vec3& N, Objeto* luzIntersectada) {
    float t_min = -1, t_tmp;
    vec3 normal;
    Objeto* objeto_intersectando = nullptr;
    for (Objeto* objeto: objetos) {
        if (luzIntersectada != nullptr) {
            if (luzIntersectada == objeto) continue;
        }
        if (objeto->interseccion(rayo, t_tmp, normal)) {
            if (t_min == -1 || t_min > t_tmp) t_min = t_tmp;
            else continue;
            p_i = rayo.ori + t_tmp*rayo.dir;
            N = normal;
            objeto_intersectando = objeto;
        }
    }
    return objeto_intersectando;
}

bool Camara :: buscar_sombra(vector<Objeto*>& objetos, Rayo& rayo_sombra) {
    float t_tmp;
    vec3 normal;
    // lanzar rayo hacia la luz
    for(Objeto* objeto_sombra: objetos) {
        // si intercecto objeto con luz, este no genera sombra
        if (objeto_sombra->idr > 0.0f) continue;
        if (objeto_sombra->luz != nullptr) continue;
        if (objeto_sombra->interseccion(rayo_sombra, t_tmp, normal)) return true;
    }
    return false;
}

vec3 Camara :: calcular_color(vector<Objeto*>& objetos, vector<Luz*>& luces, Rayo& rayo, int profundidad, Objeto* luzIntersectada) {

    if (profundidad > 4) {
        return fondo;
    }

    vec3 color = fondo;
    vec3 normal, p_i, N, L;

    Objeto* objeto_intersectando = buscar_objeto_intersectando(objetos, rayo, p_i, N, luzIntersectada);

    // en transparencia si es que el objeto interceptando

    if (objeto_intersectando) {

        // no calculo las iluminaciones del objeto de luz
        if (objeto_intersectando->luz != nullptr) {
            Luz* luz = objeto_intersectando->luz;
            double distX = p_i.x - luz->pos->x;
            double distY = p_i.y - luz->pos->y;
            float dist = sqrt(distX * distX + distY * distY);
            float normalizedDist = 1 - abs((dist) / - radioLuz);
            float factor = normalizedDist > 0.7 ? 1 : normalizedDist;
            return luz->color*factor + calcular_color(objetos, luces, rayo, profundidad+1, objeto_intersectando)*(1-factor);
            // objeto_intersectando->luz->color;
        }

        /* iluminación ambiente */
        // i_a = i_l*k_a
        vec3 i_ambiente = vec3(0.1, 0.1, 0.1) * objeto_intersectando->kd;
        vector<vec3> iluminaciones;
        for (Luz* luz: luces) {
            vec3 color_luz = fondo;
                     
            L = (*luz->pos) - p_i;
            L.normalize();
                        
            Rayo rayo_sombra(p_i + N*0.01, L);
            bool sombra = buscar_sombra(objetos, rayo_sombra);
            if (sombra){
                color_luz = objeto_intersectando->color * i_ambiente;
            } else {
                /* iluminación difusa: mate 
                    i_d = i_p*k_d*(N.L) */
                vec3 i_difusa(0, 0, 0);
                float factor_difuso = N.punto(L);
                if (factor_difuso > 0) {
                    i_difusa = luz->color * objeto_intersectando->kd * factor_difuso;
                }
                                
                /* iluminación especular: brillo */
                vec3 i_especular(0, 0, 0);
                vec3 v = -rayo.dir;
                v.normalize();
                vec3 r = 2*L.punto(N)*N-L;
                r.normalize();
                float factor_especular = r.punto(v);
                if (factor_especular > 0) {
                    i_especular = luz->color * objeto_intersectando->ks * pow(factor_difuso, objeto_intersectando->n);
                }

                /* color pixel 
                    color = color_o*(i_a+i_d) */
                color_luz = objeto_intersectando->color * (i_ambiente + i_difusa + i_especular);
            }

            bool outside = rayo.dir.punto(N) < 0;
            vec3 bias = 0.001 * N;
            
            /* Rayos Refracción */
            if(objeto_intersectando->idr > 0) {
                fresnel(rayo.dir, N, objeto_intersectando->idr, objeto_intersectando->ks);
                if (objeto_intersectando->ks < 1) {
                    float kt = 1 - objeto_intersectando->ks;
                    Rayo rayo_refractivo;
                    rayo_refractivo.ori = outside ? p_i - bias : p_i + bias;
                    rayo_refractivo.dir = refract(rayo.dir, N, objeto_intersectando->idr);
                    rayo_refractivo.dir.normalize();
                    vec3 color_refractivo = calcular_color(objetos, luces, rayo_refractivo, profundidad+1, luzIntersectada);
                    color_luz = color_luz + color_refractivo*kt;
                }
            }

            /* Rayos Reflexivos */
            if (objeto_intersectando->ks > 0) {
                vec3 v = -rayo.dir;
                v.normalize();
                Rayo rayo_reflexivo(outside ? p_i-bias : p_i+bias, 2*v.punto(N)*N - v);
                rayo_reflexivo.dir.normalize();
                vec3 color_reflexivo = calcular_color(objetos, luces, rayo_reflexivo, profundidad+1, luzIntersectada);
                color_luz = color_luz + color_reflexivo*objeto_intersectando->ks;
            }
            
            color_luz.max_to_one();
            iluminaciones.push_back(color_luz);
        }
        
        int luces_size = iluminaciones.size();
        if (iluminaciones.size() >= 1) {
            color = iluminaciones[0];
            for(int i = 1; i < luces_size; i++) {
                color = color + iluminaciones[i];
            }
            color = color/luces_size;
        }
    }

    return color;
}

vec3 Camara :: refract(vec3 I, vec3 N, float ior) {
    float cosi = clamp(-1, 1, I.punto(N));
    float etai = 1, etat = ior;
    vec3 n = N;
    if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= -N; }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? vec3(0, 0, 0) : eta * I + (eta * cosi - sqrtf(k)) * n;
}

void Camara :: fresnel(vec3 I, vec3 N, float &ior, float &kr) {
    float cosi = clamp(-1, 1, I.punto(N));
    float etai = 1, etat = ior;
    if (cosi > 0) { std::swap(etai, etat); }
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    // Total internal reflection
    if (sint >= 1) {
        kr = 1;
    }
    else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        kr = (Rs * Rs + Rp * Rp) / 2;
    }
    // As a consequence of the conservation of energy, transmittance is given by:
    // kt = 1 - kr;
}