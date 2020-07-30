#include "cuerpo.h"
#include <math.h>
#include <cmath>


cuerpo::cuerpo(float posX_, float posY_, float velX_, float velY_, float masa_, float radio_, float K_, float e_, float AY_)
{
    PX = posX_;
    PY = posY_;
    mass = masa_;
    R = radio_;
    VX = velX_;
    VY = velY_;
    AX = 0;
    AY = AY_;
    G = 9.8;
    K = K_;
    e = e_;
    V = 0;
    dt = 0.1;
}

cuerpo::~cuerpo()
{

}

float cuerpo::get_posX()
{
    return PX;
}

float cuerpo::get_posY(){//retorna la posicion en y.
    return PY;
}

float cuerpo::get_Radio(){//retorna el radio
    return R;
}

float cuerpo::get_velX(){//retorna la velocidad en x.
    return VX;
}

float cuerpo::get_velY(){//retorna la velocidad en y.
    return VY;
}

float cuerpo::get_masa(){//retorna la masa
    return mass;
}


float cuerpo::get_e(){//retorna el coeficiente de restitucion.
    return e;
}

void cuerpo::set_vel(float velx, float vely, float px, float py)
{
    VX = velx;
    VY = vely;
    PX = px;
    PY = py;
}

void cuerpo::actualizar()
{
    V = pow(((VX*VX)+(VY*VY)),1/2);
    angulo = atan2(VY, VX);
    AX = -((K*(V*V)*(R*R))/mass)*cos(angulo);
    AY = (-((K*(V*V)*(R*R))/mass)*sin(angulo))-G;
    PX = PX + (VX*dt) + ((AX*(dt*dt))/2);
    PY = PY + (VY*dt) + ((AY*(dt*dt))/2);
    VX = VX + AX*dt;
    VY = VY + AY*dt;
}


