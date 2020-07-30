#ifndef PLANET_H
#define PLANET_H

class PLANET
{
public:
    PLANET(float posX_, float posY_, float velX_, float velY_, float masa_, float radio_);
    ~PLANET();
    float getACX();
    float getACY();
    float get_posX();
    float get_posY();
    float get_Radio();
    float get_velX();
    float get_velY();
    float get_masa();
    void set_vel(float velx, float vely, float px, float py);
    void actualizar();
    void aceleracion(float,float,float,float,float);
    bool chocar=false; // Esta variable es una bandera que indica si el planeta se ha chocado o no.

private:
    float PX;//posicion en x
    float PY;//posicion en y
    float PXR; // Posicon en x del planeta que va a ser mi referencia.
    float PYR; // Posicon en y del planeta que va a ser mi referencia.
    float mass1;//masa del cuerpo
    float R;//radio del cuerpo
    float VX;//velocidad en x
    float VY;//velocidad en y
    float angulo;//angulo en el que va el cuerpo.
    float AX;//aceleracion en x
    float AY;//aceleracion en y
    float FDA;//Fuerza de atraccion.
    float V;//vector velocidad.
    float dt;//delta de tiempo.
    float DP; // Distancia entre los planetas.
    float G; // Constante gravitacional.
};

#endif // PLANET_H
