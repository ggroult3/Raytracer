#include "vect.h"
#include <math.h>
#include <iostream>
using namespace std;

#include <random>
static default_random_engine engine(52);
static uniform_real_distribution<double> uniform(0,1);

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

Vect operator*(const Vect& a,const Vect& b){
    return Vect(a[0]*b[0],a[1]*b[1],a[2]*b[2]);
}

Vect operator/(const Vect& a, double b){
    return Vect(a[0]/b,a[1]/b,a[2]/b);
}

Vect cross(const Vect& a,const Vect& b){
    return Vect(a[1] * b[2] - b[1] * a[2],a[2]*b[0]-b[2]*a[0],a[0]*b[1]-b[0]*a[1]);
}

double dot(const Vect& a,const Vect& b){
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

double sqr(double x){
    return x*x;
}

Vect random_cos(const Vect &N){
    double u1 = uniform(engine);
    double u2 = uniform(engine);
    double x = cos(2 * M_PI * u1) * sqrt(1 - u2);
    double y = sin(2 * M_PI * u1) * sqrt(1 - u2);
    double z = sqrt(u2);
    Vect T1;
    if (N[0] < N[1] && N[0] < N[2]) {
        T1 = Vect(0,N[2],-N[1]);
    }
    else {
        if (N[1] < N[2] && N[1] < N[0]) {
            T1 = Vect(N[2],0,-N[0]);
        }
        else {
            T1 = Vect(N[1],-N[0],0);
        }
    }
    T1 = T1.get_normalized();
    Vect T2 = cross(N,T1);
    return z * N + x * T1 + y * T2;
}
