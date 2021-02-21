#include "scene.h"
#include <vector>
#include <math.h>
#include <vect.h>
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

bool Scene::intersect(Ray &r, Vect &P, Vect &N, Vect &albedo, bool &mirror,bool &transp, double &t){
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
            mirror = objects[i].get_isMirror();
            transp = objects[i].get_isTransp();
        }
    }
    return has_inter;
}

Vect Scene::getColor(Ray &r,int rebond){
    Vect P,N,albedo;
    double t;
    bool mirror,transp;
    bool inter = intersect(r,P,N,albedo,mirror,transp,t); // Determine s'il y a intersection entre la sphere et le rayon : si oui, P indique le point d'intersection sphere-ray et N le vecteur normale a la sphere au point P
    Vect color(0.,0.,0.);

    if (inter && rebond < 5){

        if (mirror){
            Vect reflectedDir = r.get_u() - 2 * dot(r.get_u(),N) * N;
            Ray reflectedRay(P + 0.001*N,reflectedDir);
            return getColor(reflectedRay,rebond + 1);
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

                return getColor(refractedRay,rebond + 1);
            }
            else {
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

                return color;
            }

        }

    }

}
