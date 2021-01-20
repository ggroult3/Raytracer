#include "sphere.h"

Sphere::Sphere(const Vect& O1,double R1){
    O = O1;
    R = R1;
}

Vect& Sphere::get_O(){
    return O;
}

double Sphere::get_R(){
    return R;
}

bool Sphere::intersect(Ray &r){
    // solves a*t^2 + b*t + c = 0
    double a = 1;
    Vect& u = r.get_u();
    Vect& C = r.get_C();
    double b = 2 * dot(u,C - O);
    double c = O.sqrNorm() - get_R()*get_R();
    double delta = b*b - 4 * a*c;
    if (delta >= 0) return true;

    return false;
}
