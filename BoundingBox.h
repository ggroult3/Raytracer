#pragma once
#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include "Vect.h"
#include "Ray.h"

class BoundingBox
{
public:
    BoundingBox();
    bool intersect(Ray& r);
    Vect& get_mini();
    Vect& get_maxi();
    void set_mini(Vect minVect);
    void set_mini(double value, int i);
    void set_maxi(Vect maxVect);
    void set_maxi(double value, int i);
private:
    Vect mini, maxi;
};

#endif // BOUNDINGBOX_H
