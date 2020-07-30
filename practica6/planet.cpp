#include "planet.h"
#include <math.h>
#include <cmath>
#include <QDebug>
#define PI 3.14159265
PLANET::PLANET(float posX_, float posY_, float velX_, float velY_, float masa_, float radio_)
{
    PX = posX_;
    PY = posY_;
    mass1 = masa_;
    R = radio_;
    VX = velX_;
    VY = velY_;
    AX = 0;
    AY = 0;
    V = 0;
    dt = 0.1;
    G=0.1;
}

PLANET::~PLANET()
{

}

float PLANET::getACX()
{
    return AX;
}

float PLANET::getACY()
{
    return AY;
}

float PLANET::get_posX()
{
    return PX;
}

float PLANET::get_posY(){//retorna la posicion en y.
    return PY;
}

float PLANET::get_Radio(){//retorna el radio
    return R;
}

float PLANET::get_velX(){//retorna la velocidad en x.
    return VX;
}

float PLANET::get_velY(){//retorna la velocidad en y.
    return VY;
}

float PLANET::get_masa(){//retorna la masa
    return mass1;
}

void PLANET::set_vel(float velx, float vely, float px, float py)
{
    VX = velx;
    VY = vely;
    PX = px;
    PY = py;
}


void PLANET::aceleracion(float PX2,float PY2,float mass2,float AXA,float AYA){
    angulo = atan2(PY2-PY, PX2-PX);
    DP=pow(pow(PX2-PX,2)+pow(PY2-PY,2),0.5);
    if(AXA==AX and AYA==AY){
        AX=0;
        AY=0;
    }
    AX +=(((G*mass2)/(DP*DP))*cos(angulo));
    AY +=(((G*mass2)/(DP*DP))*sin(angulo));
}

void PLANET::actualizar()
{
    VX = VX + AX*dt;
    VY = VY + AY*dt;
    PX = PX + (VX*dt) + ((AX*(dt*dt))/2);
    PY = PY + (VY*dt) + ((AY*(dt*dt))/2);
}
