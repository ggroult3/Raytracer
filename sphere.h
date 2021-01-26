#ifndef SPHERE_H
#define SPHERE_H

#include<vect.h>
#include<ray.h>

class Sphere
{
public:
    Sphere(const Vect& O, double R);
    Vect& get_O();
    double get_R();
    bool intersect(Ray& r,Vect& P,Vect& N);

private:
    Vect O;
    double R;
};

#endif // SPHERE_H
