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
    double get_I();
    Vect& get_L();
    void push(Sphere object);
    int get_objects_size();
    bool intersect(Ray& r,Vect& P,Vect& N,Vect& albedo,bool& mirror,bool& transp,double& t,int& objectid);
    Vect getColor(Ray& r,int rebond);
private:
    double I;
    Vect L;
    vector<Sphere> objects;
};

#endif // SCENE_H
