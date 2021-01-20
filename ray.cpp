#include "ray.h"

Ray::Ray(const Vect& C1, const Vect& u1){
    C = C1;
    u = u1;
}

Vect& Ray::get_u(){
    return u;
}

Vect& Ray::get_C(){
    return C;
}
