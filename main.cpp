#include <iostream>

using namespace std;

#include <time.h>

#define _CRT_SECURE_NO_WARNINGS 1
#include <vector>
#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//#define M_PI 3.141592653589793238562;

#include <vect.h>
#include <ray.h>
#include <sphere.h>
#include <scene.h>

#include <algorithm>

int main()
{
    time_t beginTime,endTime;
    time(&beginTime);

    int W = 512; // Largeur de l'image
    int H = 512; // Hauteur de l'image

    Scene scene;

    Vect C(0,0,55); // Position de la camera
    double fov = 60 * M_PI / 180; // Champ de vision de la camera


    Sphere S1(Vect(0,0,0),10,Vect(1.,0.3,0.2));
    Sphere Ssol(Vect(0,-1000,0),990,Vect(1.,1.,1.));
    Sphere Smur1(Vect(-1000,0,0),940,Vect(1.,0.,0.));
    Sphere Smur2(Vect(1000,0,0),940,Vect(0.,1.,0.));
    Sphere Smur3(Vect(0,0,-1000),940,Vect(0.,0.,1.));
    Sphere Smur4(Vect(0,0,1000),940,Vect(1.,1.,0.));
    Sphere Splafond(Vect(0,1000,0),940,Vect(1.,1.,1.));
    scene.push(S1);
    scene.push(Smur1);
    scene.push(Smur2);
    scene.push(Smur3);
    scene.push(Smur4);
    scene.push(Splafond);
    scene.push(Ssol);

    double I = 1E7;// Intensité lumineuse
    Vect rho(1,0,0);
    Vect L(-10,20,40);// Coordonnees de la lampe

    vector<unsigned char> image(W*H * 3,0);
    for (int i = 0 ; i < H; i++){
        for (int j = 0 ; j < W ; j++){
            Vect u(j - W / 2,i - H / 2, - W / (2.*tan(fov/2))); // Vecteur directeur du rayon émis de la caméra
            u = u.get_normalized(); // Le vecteur directeur doit être unitaire
            Vect P,N,albedo;
            Ray r(C,u);
            bool inter = scene.intersect(r,P,N,albedo); // Determine s'il y a intersection entre la sphere et le rayon : si oui, P indique le point d'intersection sphere-ray et N le vecteur normale a la sphere au point P
            Vect color(0,0,0);
            if (inter){
                Vect PL = L - P;
                double d = sqrt(PL.sqrNorm());
                color = I/(4*M_PI*d*d) * albedo/M_PI * max(0.,dot(N,PL/d));
            }

            // On inverse l'image en remplacant (i*W+j) par ((H - i -1)*W+j)
            image[((H - i -1)*W+j) * 3 + 0] = min(255.,color[0]);
            image[((H - i -1)*W+j) * 3 + 1] = min(255.,color[1]);
            image[((H - i -1)*W+j) * 3 + 2] = min(255.,color[2]);

        }
    }

    stbi_write_png("image_create_scene.png",W,H,3,&image[0],0);

    time(&endTime);
    cout << "Cela dure " << difftime(endTime,beginTime) << " seconde(s) !" << endl;
    return 0;
}
