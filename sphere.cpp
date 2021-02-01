#include "sphere.h"
#include <iostream>
#include <math.h>

using namespace std;

Sphere::Sphere(const Vect& O1,double R1,const Vect& albedo1){
    O = O1;
    R = R1;
    albedo = albedo1;
}

Vect& Sphere::get_O(){
    return O;
}

double Sphere::get_R(){
    return R;
}

Vect& Sphere::get_albedo(){
    return albedo;
}

bool Sphere::intersect(Ray &r,Vect& P,Vect& N,double& t){
    // solves a*t^2 + b*t + c = 0
    double a = 1;
    double b = 2 * dot(r.get_u(),r.get_C() - O);
    double c = (r.get_C()-O).sqrNorm() - get_R()*get_R();
    double delta = b*b - 4 * a*c;
    if (delta < 0) return false;

    double sqDelta = sqrt(delta);

    double t2 = (- b + sqDelta) / (2 * a);
    if (t2 < 0) return false;

    double t1 = (- b - sqDelta) / (2 * a);
    if (t1 > 0)
        t = t1;
    else
        t = t2;

    P = r.get_C() + t*r.get_u(); // Point d'intersection le plus proche de la caméra
    N = (P - O).get_normalized();

    return true;
}
