#ifndef RAY_H
#define RAY_H

#include <vect.h>

class Ray
{
public:
    Ray(const Vect& C1,const Vect& u1);
    Vect& get_C();
    Vect& get_u();
private:
    Vect C,u;
};

#endif // RAY_H
