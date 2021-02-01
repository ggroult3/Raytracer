#ifndef SCENE_H
#define SCENE_H

#include <sphere.h>
#include <vector>
#include <ray.h>
#include <vect.h>

using namespace std;


class Scene
{
public:
    Scene();
    void set_I(double I1);
    void set_L(Vect L1);
    void push(Sphere object);
    int get_objects_size();
    bool intersect(Ray& r,Vect& P,Vect& N,Vect& albedo);
private:
    double I;
    Vect L;
    vector<Sphere> objects;
};

#endif // SCENE_H
