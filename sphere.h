#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "Vect.h"
#include "Ray.h"
#include "Object.h"

class Sphere : public Object
{
public:
    Sphere(const Vect& O, double R, const Vect& albedo);
    Sphere(const Vect& O, double R, const Vect& albedo, bool isMirror);
    Sphere(const Vect& O, double R, const Vect& albedo, bool isMirror, bool isTransp);
    Vect& get_O();
    double get_R();
    Vect& get_albedo();
    bool& get_isMirror();
    bool& get_isTransp();
    bool intersect(Ray& r, Vect& P, Vect& N, double& t,Vect& color);

private:
    Vect O;
    double R;
    Vect albedo;
    bool isMirror;
    bool isTransp;
};

#endif // SPHERE_H


