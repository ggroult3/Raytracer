#include "sphere.h"
#include <iostream>
using namespace std;

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
    double R = get_R();
    double b = 2 * dot(r.get_u(),r.get_C() - O);
    double c = (r.get_C()-O).sqrNorm() - R*R;
    double delta = b*b - 4 * a*c;
    if (delta >= 0) return true;

    return false;
}
