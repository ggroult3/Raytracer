#include "scene.h"
#include <vector>
using namespace std;

Scene::Scene(){

}

void Scene::set_I(double I1){
    I = I1;
}

void Scene::set_L(Vect L1){
    L = L1;
}

void Scene::push(Sphere object){
    objects.push_back(object);
}

int Scene::get_objects_size(){
    return objects.size();
}

bool Scene::intersect(Ray &r, Vect &P, Vect &N, Vect &albedo, double &t){
    t = 1E10;
    bool has_inter = false;
    for (int i = 0 ; i < get_objects_size(); i++){
        Vect localP, localN;
        double localt;
        if (objects[i].intersect(r,localP,localN,localt) && localt < t){
            t = localt;
            has_inter = true;
            albedo = objects[i].get_albedo();
            P = localP;
            N = localN;
        }
    }
    return has_inter;
}
