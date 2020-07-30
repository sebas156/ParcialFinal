#include "cuerpoquecae.h"
#include <math.h>

CuerpoQueCae::CuerpoQueCae(float posX_, float posY_, float velX_, float velY_, float masa_, float radio_, float K_, float e_)
{
    PX = posX_;
    PY = posY_;
    mass = masa_;
    R = radio_;
    VX = velX_;
    VY = velY_;
    AX = 0;
    AY = 0;
    G = 9.8;
    K = K_;
    e = e_;
    V = 0;
    dt = 0.1;
}

float CuerpoQueCae::get_posX()
{
    return PX;
}

float CuerpoQueCae::get_posY(){//retorna la posicion en y.
    return PY;
}

float CuerpoQueCae::get_Radio(){//retorna el radio
    return R;
}

float CuerpoQueCae::get_velX(){//retorna la velocidad en x.
    return VX;
}

float CuerpoQueCae::get_velY(){//retorna la velocidad en y.
    return VY;
}

float CuerpoQueCae::get_masa(){//retorna la masa
    return mass;
}


float CuerpoQueCae::get_e(){//retorna el coeficiente de restitucion.
    return e;
}

void CuerpoQueCae::set_vel(float velx, float vely, float px, float py)
{
    VX = velx;
    VY = vely;
    PX = px;
    PY = py;
}

void CuerpoQueCae::actualizar()
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


