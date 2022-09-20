
void Escenario1(Camara& camara) {
    vector<Luz*> luces; 
    luces.push_back(new Luz(vec3(10, 30, 20), vec3(1, 1, 1)));
    luces.push_back(new Luz(vec3(-10, 30, 20), vec3(1, 1, 1)));


    vector<Objeto*> objetos; 
    objetos.push_back(new Esfera(vec3(1, 1, 0), 0.9, 0.5, 40, 0, vec3(6, 1, 7), 3)); 
    objetos.push_back(new Esfera(vec3(1, 0.3, 0), 0.9, 0.5, 80, 0, vec3(-2, 0, 13), 0.5));
    objetos.push_back(new Esfera(vec3(0.1, 0.7, 1), 0.9, 0.5, 30, 0, vec3(-3, -2, 10), 2.5));
    objetos.push_back(new Esfera(vec3(0.5, 0.9, 0.7), 0.9, 0.5, 30, 0, vec3(1, 2, 0), 5));
    objetos.push_back(new Esfera(vec3(0.2, 0.2, 0.7), 0.9, 0.9, 30, 0, vec3(-2, 10, 6), 3));

    objetos.push_back(new Plano(vec3(0.5, 0.9, 0.9), 0.7, 0, 10, 0, vec3(0,1,0), 2));

    Mundo mundo(camara, luces, objetos);
    mundo.Escenario();
}

void Escenario2(Camara& camara) {
    vector<Luz*> luces; 
    luces.push_back(new Luz(vec3(10, 30, 20), vec3(1, 1, 1)));

    vector<Objeto*> objetos; 
    for (int i = -20; i <= 20; i+=5) {
        srand(i+1);
        vec3 color((rand()%10)/10.0, (rand()%10)/10.0, (rand()%10)/10.0);
        for (int j = -20; j <= 20; j+=5) {
            float kd = (rand()%10+1)/10.0;
            float ks = (rand()%10+1)/10.0;
            vec3 pos(i, 4, j);
            int radio = 2;
            objetos.push_back(new Esfera(color, kd, ks, (rand()%200)+40, 0, pos, radio));
        }
   }
    
    objetos.push_back(new Plano(vec3(0.4, 0.5, 0.2), 0.7, 0, 10, 0, vec3(0,1,0), 2));

    Mundo mundo(camara, luces, objetos);
    mundo.Escenario();
}

void LuciernagasBeta(Camara& camara) {
    vector<Luz*> luces; 
    
    // luces.push_back(new Luz(vec3(-2, 10, 6), vec3(1, 1, 1)));
    // luces.push_back(new Luz(vec3(10, 30, 20), vec3(1, 1, 1)));
    // luces.push_back(new Luz(vec3(-10, 30, 20), vec3(1, 1, 1)));

    vector<Objeto*> objetos; 

    vec3 centroLuciernaga(0, 3, 7);
    Luz* luciernaga = new Luz(centroLuciernaga, vec3(0, 1, 1)); 
    luces.push_back(luciernaga);
    objetos.push_back(new Esfera(vec3(0.2, 0.2, 0.7), 0.9, 0.9, 30, 0, centroLuciernaga, 1, luciernaga));

    vec3 centroLuciernaga2(12, 3, 7);
    Luz* luciernaga2 = new Luz(centroLuciernaga2, vec3(1, 0, 1)); 
    luces.push_back(luciernaga2);
    objetos.push_back(new Esfera(vec3(0.2, 0.2, 0.7), 0.9, 0.9, 30, 0, centroLuciernaga2, 1, luciernaga2));

    objetos.push_back(new Esfera(vec3(1, 1, 0), 0.9, 0.5, 40, 0, vec3(6, 1, 7), 3)); 

    objetos.push_back(new Plano(vec3(0.5, 0.9, 0.9), 0.7, 0, 10, 0, vec3(0,1,0), 2));

    Mundo mundo(camara, luces, objetos);
    mundo.Escenario();
}

void LuciernagasAlfa(Camara& camara) {
    vector<Luz*> luces; 
    vector<Objeto*> objetos; 

    luces.push_back(new Luz(vec3(-2, 15, 6), vec3(1, 1, 1)));    

    vec3 centroLuciernaga(0, 6, 7);
    Luz* luciernaga = new Luz(centroLuciernaga, vec3(0, 1, 1)); 
    luces.push_back(luciernaga);
    objetos.push_back(new Esfera(vec3(0.2, 0.2, 0.7), 0.9, 0.9, 30, 0, centroLuciernaga, 1, luciernaga));

    vec3 centroLuciernaga2(12, 6, 7);
    Luz* luciernaga2 = new Luz(centroLuciernaga2, vec3(1, 0, 1)); 
    luces.push_back(luciernaga2);
    objetos.push_back(new Esfera(vec3(0.2, 0.2, 0.7), 0.9, 0.9, 30, 0, centroLuciernaga2, 1, luciernaga2));

    // objetos.push_back(new Esfera(vec3(1, 1, 0), 0.9, 0.5, 40, 1, vec3(6, 15, 7), 2)); 

    objetos.push_back(new Esfera(vec3(1, 1, 1), 0.9, 0.5, 40, 0, vec3(6, 6, -7), 2)); 

    objetos.push_back(new Cilindro(vec3(1, 1, 0), 0.9, 0.5, 30, 1, vec3(6, 1, 7), vec3(6, 10, 7), 3));
    objetos.push_back(new Plano(vec3(0.5, 0.9, 0.9), 0.7, 0, 10, 0, vec3(0, 1, 0), 2));

    Mundo mundo(camara, luces, objetos);
    mundo.Escenario();
}

void LuciernagasGamma(Camara& camara) {

    vector<Luz*> luces; 
    vector<Objeto*> objetos; 

    // luces.push_back(new Luz(vec3(10, 30, 20), vec3(1, 1, 1)));

    vec3 centroLuciernaga(2, 9, 7);
    Luz* luciernaga = new Luz(centroLuciernaga, vec3(0, 1, 1)); 
    luces.push_back(luciernaga);
    objetos.push_back(new Esfera(vec3(0.2, 0.2, 0.7), 0.9, 0.9, 30, 0, centroLuciernaga, radioLuz, luciernaga));

    vec3 centroLuciernaga2(8, 9, 7);
    Luz* luciernaga2 = new Luz(centroLuciernaga2, vec3(1, 0.01, 0.01)); 
    luces.push_back(luciernaga2);
    objetos.push_back(new Esfera(vec3(1, 0.01, 0.01), 0.9, 0.9, 30, 0, centroLuciernaga2, radioLuz, luciernaga2));

    objetos.push_back(new Esfera(vec3(1, 1, 1), 0.9, 0.5, 40, 0, vec3(4, 6, 7), 1)); 


    vec3 centroLuciernaga3(-5, 9, 7);
    Luz* luciernaga3 = new Luz(centroLuciernaga3, vec3(1, 0, 1)); 
    luces.push_back(luciernaga3);
    objetos.push_back(new Esfera(vec3(1, 0, 1), 0.9, 0.9, 30, 0, centroLuciernaga3, radioLuz, luciernaga3));
    // esfera atrás
    objetos.push_back(new Esfera(vec3(1, 1, 1), 0.9, 0.5, 40, 0, vec3(-8, 9, 2), 2)); 

    objetos.push_back(new Cilindro(vec3(1, 1, 1), 0.9, 0.1, 30, 1, vec3(6, 2, 2), vec3(6, 10, 2), 7));
    objetos.push_back(new Cilindro(vec3(1, 1, 1), 0.9, 0.1, 30, 1, vec3(6, 2, 2), vec3(6, 10, 2), 6.5));

    objetos.push_back(new Plano(vec3(0.5, 0.9, 0.9), 0.7, 0, 10, 0, vec3(0, 1, 0), 2));


    Mundo mundo(camara, luces, objetos);
    mundo.Escenario();
}
