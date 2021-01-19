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
