#ifndef SPHERE_H
#define SPHERE_H

#include<vect.h>
#include<ray.h>

class Sphere
{
public:
    Sphere(const Vect& O, double R, const Vect& albedo);
    Vect& get_O();
    double get_R();
    Vect& get_albedo();
    bool intersect(Ray& r,Vect& P,Vect& N,double& t);

private:
    Vect O;
    double R;
    Vect albedo;
};

#endif // SPHERE_H
