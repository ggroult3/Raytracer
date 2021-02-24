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

#include <random>
static default_random_engine engine(52);
static uniform_real_distribution<double> uniform(0,1);

void integrateCos(){
    int N = 10000;
    double sigma = 0.25;
    double s = 0;
    for (int i = 0; i < N; i++){
        double u1 = uniform(engine);
        double u2 = uniform(engine);
        double u3 = uniform(engine);
        double u4 = uniform(engine);

        double x1 = sigma * cos(2 * M_PI * u1) * sqrt(-2 * log(u2));
        double x2 = sigma * sin(2 * M_PI * u1) * sqrt(-2 * log(u2));
        double x3 = sigma * cos(2 * M_PI * u3) * sqrt(-2 * log(u4));
        double x4 = sigma * sin(2 * M_PI * u3) * sqrt(-2 * log(u4));

        double p1 = 1 / (sigma*sqrt(2 * M_PI)) * exp(-x1 * x1 / (2 * sigma * sigma));
        double p2 = 1 / (sigma*sqrt(2 * M_PI)) * exp(-x2 * x2 / (2 * sigma * sigma));
        double p3 = 1 / (sigma*sqrt(2 * M_PI)) * exp(-x3 * x3 / (2 * sigma * sigma));
        double p4 = 1 / (sigma*sqrt(2 * M_PI)) * exp(-x4 * x4 / (2 * sigma * sigma));

        double p = p1 * p2 * p3 * p4;

        if (x1 > -M_PI/2 && x1 < M_PI/2 && x2 > -M_PI/2 && x2 < M_PI/2 && x3 > -M_PI/2 && x3 < M_PI/2 && x4 > -M_PI/2 && x4 < M_PI/2)
                s = s + pow(cos(x1 + x2 + x3 + x4),2) / p / N;
    }
    cout << s << endl;
}

int main()
{
    time_t beginTime,endTime;
    time(&beginTime);

    //integrateCos();

    int W = 512; // Largeur de l'image
    int H = 512; // Hauteur de l'image

    Scene scene;

    Vect C(0,0,55); // Position de la camera
    double fov = 60 * M_PI / 180; // Champ de vision de la camera


    Sphere S1(Vect(0,0,0),10,Vect(1.,0.3,0.2));
    Sphere S2(Vect(-20,0,0),10,Vect(1.,0.3,0.2),true);
    Sphere S3(Vect(20,0,0),10,Vect(1.,0.3,0.2),false,true);
    Sphere Ssol(Vect(0,-1000,0),990.,Vect(1.,1.,1.));
    Sphere Smur1(Vect(-1000,0,0),940.,Vect(1.,0.,0.));
    Sphere Smur2(Vect(1000,0,0),940.,Vect(0.,1.,0.));
    Sphere Smur3(Vect(0,0,-1000),940.,Vect(0.,0.,1.));
    Sphere Smur4(Vect(0,0,1000),940.,Vect(1.,1.,0.));
    Sphere Splafond(Vect(0,1000,0),940.,Vect(1.,1.,1.));
    scene.push(S1);
    scene.push(S2);
    scene.push(S3);
    scene.push(Smur1);
    scene.push(Smur2);
    scene.push(Smur3);
    scene.push(Smur4);
    scene.push(Splafond);
    scene.push(Ssol);

    // double I = 1E7;// Intensité lumineuse sans correction gamma
    double I = 5E9;// Intensité lumineuse avec correction gamma
    Vect L(-10,20,40);// Coordonnees de la lampe
    scene.set_I(I);
    scene.set_L(L);

    int nbRays = 100;

    vector<unsigned char> image(W*H * 3,0);
#pragma fomp parallel for schedule(dynamic,1);
    for (int i = 0 ; i < H; i++){
        for (int j = 0 ; j < W ; j++){
            Vect u(j - W / 2,i - H / 2, - W / (2.*tan(fov/2))); // Vecteur directeur du rayon émis de la caméra
            u = u.get_normalized(); // Le vecteur directeur doit être unitaire
            Ray r(C,u);
            Vect color(0,0,0);

            for(int k = 0; k < nbRays; k++)
                color = color + scene.getColor(r,0);
            color = color / nbRays;

            // On inverse l'image en remplacant (i*W+j) par ((H - i -1)*W+j)
            /*
            image[((H - i -1)*W+j) * 3 + 0] = min(255.,color[0]);
            image[((H - i -1)*W+j) * 3 + 1] = min(255.,color[1]);
            image[((H - i -1)*W+j) * 3 + 2] = min(255.,color[2]);
            */

            // On applique la correction gamma à l'image
            image[((H - i -1)*W+j) * 3 + 0] = min(255.,pow(color[0],0.45));
            image[((H - i -1)*W+j) * 3 + 1] = min(255.,pow(color[1],0.45));
            image[((H - i -1)*W+j) * 3 + 2] = min(255.,pow(color[2],0.45));
        }
    }

    stbi_write_png("image_eclairage_indirecte.png",W,H,3,&image[0],0);

    time(&endTime);
    cout << "Cela dure " << difftime(endTime,beginTime) << " seconde(s) !" << endl;
    return 0;
}
