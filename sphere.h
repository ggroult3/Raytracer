#ifndef SPHERE_H
#define SPHERE_H

#include<vect.h>
#include<ray.h>

class Sphere
{
public:
    Sphere(const Vect& O, double R, const Vect& albedo);
    Sphere(const Vect& O, double R, const Vect& albedo, bool isMirror);
    Sphere(const Vect& O, double R, const Vect& albedo, bool isMirror,bool isTransp);
    Vect& get_O();
    double get_R();
    Vect& get_albedo();
    bool& get_isMirror();
    bool& get_isTransp();
    bool intersect(Ray& r,Vect& P,Vect& N,double& t);

private:
    Vect O;
    double R;
    Vect albedo;
    bool isMirror;
    bool isTransp;
};

#endif // SPHERE_H
