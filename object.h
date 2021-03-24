#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "Vect.h"
#include "Ray.h"

class Object
{
public:
    Object();
    virtual bool intersect(Ray& r, Vect& P, Vect& normale, double& t) = 0;
    virtual Vect& get_albedo() = 0;
    virtual bool& get_isMirror() = 0;
    virtual bool& get_isTransp() = 0;
private:
    Vect albedo;
    bool isMirror;
    bool isTransp;
};

#endif // OBJECT_H


