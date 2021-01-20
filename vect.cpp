#include "vect.h"
#include <math.h>

Vect::Vect(double x,double y,double z){
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
}

double Vect::operator[](int i) const{
    return coords[i];
}

double& Vect::operator[](int i){
    return coords[i];
}

double Vect::sqrNorm(){
    return coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2];
}

Vect Vect::get_normalized(){
    double n = sqrt(sqrNorm());
    return Vect(coords[0] / n,coords[1] / n,coords[2] / n);
}

Vect operator+(const Vect& a, const Vect& b){
    return Vect(a[0] + b[0],a[1] + b[1],a[2] + b[2]);
}

Vect operator-(const Vect& a, const Vect& b){
    return Vect(a[0] - b[0],a[1] - b[1],a[2] - b[2]);
}

Vect operator-(const Vect& a){
    return Vect(-a[0],-a[1],-a[2]);
}

Vect operator*(const Vect& a, double b){
    return Vect(a[0]*b,a[1]*b,a[2]*b);
}

Vect operator*(double a,const Vect& b){
    return Vect(a*b[0],a*b[1],a*b[2]);
}

Vect operator/(const Vect& a, double b){
    return Vect(a[0]/b,a[1]/b,a[2]/b);
}

double dot(const Vect& a,const Vect& b){
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

double sqr(double x){
    return x*x;
}
