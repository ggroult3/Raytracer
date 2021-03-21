#include "scene.h"
#include <vector>
#include <math.h>
#include <vect.h>
#include <algorithm>
#include <iostream>
using namespace std;

Scene::Scene(){

}

void Scene::set_I(double I1){
    I = I1;
}

void Scene::set_L(Vect L1){
    L = L1;
}

double Scene::get_I(){
    return I;
}

Vect& Scene::get_L(){
    return L;
}

void Scene::push(Object* object){
    objects.push_back(object);
}

int Scene::get_objects_size(){
    return objects.size();
}

bool Scene::intersect(Ray &r, Vect &P, Vect &N, Vect &albedo, bool &mirror,bool &transp, double &t,int &objectid){
    t = 1E10;
    bool has_inter = false;
    for (int i = 0 ; i < get_objects_size(); i++){
        Vect localP, localN;
        double localt;
        bool intersect_result = objects[i]->intersect(r,localP,localN,localt);
        if (intersect_result && localt < t){
            t = localt;
            has_inter = true;
            albedo = objects[i]->get_albedo();
            P = localP;
            N = localN;
            mirror = objects[i]->get_isMirror();
            transp = objects[i]->get_isTransp();
            objectid = i;
        }
    }
    return has_inter;
}

Vect Scene::getColor(Ray &r,int rebond,bool lastDiffus){
    Vect P,N,albedo;
    double t;
    bool mirror,transp;
    int objectid;
    bool inter = intersect(r,P,N,albedo,mirror,transp,t,objectid); // Determine s'il y a intersection entre la sphere et le rayon : si oui, P indique le point d'intersection sphere-ray et N le vecteur normale a la sphere au point P
    Vect color(0.,0.,0.);



    if (inter && rebond < 10){

        if (objectid == 0){
            if (rebond == 0 || !lastDiffus){
                double I = get_I();
                return Vect(I,I,I) / (4 * M_PI * M_PI * dynamic_cast<Sphere*>(objects[0])->get_R() * dynamic_cast<Sphere*>(objects[0])->get_R());
            }
            else{
                return Vect(0, 0, 0);
            }
        }
        else{
            if (mirror){
                Vect reflectedDir = r.get_u() - 2 * dot(r.get_u(),N) * N;
                Ray reflectedRay(P + 0.001*N,reflectedDir);
                return getColor(reflectedRay,rebond + 1,false);
            }
            else {
                if (transp){
                    double n1 = 1, n2 = 1.4;
                    Vect N2 = N;
                    if (dot(r.get_u(),N) > 0) { // Cas ou on sort de la sphere
                        swap(n1,n2);
                        N2 = -N;
                    }
                    Vect Tt = n1 / n2 * (r.get_u() - dot(r.get_u(),N2)*N2);
                    double rad = 1 - (n1 / n2) * (n1 / n2) * (1 - (dot(r.get_u(),N2)) * (dot(r.get_u(),N2)));
                    Vect Tn = -sqrt(rad)*N2;

                    Vect refractedDir = Tt + Tn;
                    Ray refractedRay(P - 0.001*N2,refractedDir);

                    return getColor(refractedRay,rebond + 1,false);
                }
                else {
                    //eclairage direct (premiere version)
                    /*
                    Vect PL = L - P;
                    double d = sqrt(PL.sqrNorm());
                    Vect shadowP, shadowN, shadowAlbedo;
                    double shadowt;
                    Ray shadowRay(P+0.001*N,PL/d); // On decale legerement le rayon pour eviter les effets de bords avec la sphere (suppression du bruit d'ombre)
                    bool shadowMirror,shadowTransp;
                    bool shadowInter = intersect(shadowRay,shadowP,shadowN,shadowAlbedo,shadowMirror,shadowTransp,shadowt); // Determine s'il y a intersection entre la sphère et un rayon émis de la source de lumière
                    if (shadowInter && shadowt < d){ // S'il y a intersection, on vérifie que la distance le point d'intersection et le sol soit inférieur à la distance sol-source de lumière. Si oui, on envoie un pixel noir, sinon la couleur attendue
                        color = Vect(0.,0.,0.);
                    }
                    else{
                        color = I/(4*M_PI*d*d) * albedo/M_PI * max(0.,dot(N,PL/d));
                    }
                    */

                    // eclairage direct avec ombre douce
                    Vect PL = L - P;
                    PL = PL.get_normalized();
                    Vect omega = random_cos(-PL);
                    Vect xprime = omega * dynamic_cast<Sphere*>(objects[0])->get_R() + dynamic_cast<Sphere*>(objects[0])->get_O();
                    Vect P_xprime = xprime - P;
                    double d = sqrt(P_xprime.sqrNorm());
                    P_xprime = P_xprime / d;

                    Vect shadowP, shadowN, shadowAlbedo;
                    double shadowt;
                    Ray shadowRay(P+0.001*N,P_xprime/d); // On decale legerement le rayon pour eviter les effets de bords avec la sphere (suppression du bruit d'ombre)
                    bool shadowMirror,shadowTransp;
                    int objectid;
                    bool shadowInter = intersect(shadowRay,shadowP,shadowN,shadowAlbedo,shadowMirror,shadowTransp,shadowt,objectid); // Determine s'il y a intersection entre la sphère et un rayon émis de la source de lumière
                    if (shadowInter && shadowt < d-0.0001){ // S'il y a intersection, on vérifie que la distance le point d'intersection et le sol soit inférieur à la distance sol-source de lumière. Si oui, on envoie un pixel noir, sinon la couleur attendue
                        color = Vect(0.,0.,0.);
                    }
                    else {
                        double R2 = (dynamic_cast<Sphere*>(objects[0])->get_R()) * (dynamic_cast<Sphere*>(objects[0])->get_R());
                        double proba = max(0.,dot(-PL,omega)) / (M_PI * dynamic_cast<Sphere*>(objects[0])->get_R() * dynamic_cast<Sphere*>(objects[0])->get_R());
                        double J = max(0.,dot(omega, -P_xprime))/(d*d);
                        color = I / (4 * M_PI * M_PI * R2) * albedo / M_PI * max(0.,dot(N,P_xprime)) * J / proba;
                    }


                }
                // eclairage indirect
                Vect omega_i = random_cos(N);
                Ray rayOmega_i(P + 0.001*N,omega_i);
                Vect indirectColor = getColor(rayOmega_i,rebond + 1,true);

                color = color + albedo * indirectColor;
            }

        }




    }

    return color;

}
