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



int main()
{
    time_t beginTime,endTime;
    time(&beginTime);

    int W = 512; // Largeur de l'image
    int H = 512; // Hauteur de l'image

    Vect C(0,0,55); // Position de la camera
    double fov = 60 * M_PI / 180; // Champ de vision de la camera

    Vect O(0,0,0); // Centre de la sphère
    double R = 10; // Rayon de la sphère
    Sphere S(O,R);

    vector<unsigned char> image(W*H * 3,0);
    for (int i = 0 ; i < H; i++){
        for (int j = 0 ; j < W ; j++){
            Vect u(j - W / 2,i - H / 2, - W / (2.*tan(fov/2))); // Vecteur directeur du rayon émis de la caméra
            u = u.get_normalized(); // Le vecteur directeur doit être unitaire
            Ray r(C,u);
            bool inter = S.intersect(r); // Determine s'il y a intersection entre la sphere et le rayon : si oui, le pixel est blanc, sinon il est noir
            Vect color(0,0,0);
            if (inter){
                color = Vect(255,255,255);
            }

            image[(i*W+j) * 3 + 0] = color[0];
            image[(i*W+j) * 3 + 1] = color[1];
            image[(i*W+j) * 3 + 2] = color[2];

        }
    }

    stbi_write_png("image_detect_sphere.png",W,H,3,&image[0],0);

    time(&endTime);
    cout << "Cela dure " << difftime(endTime,beginTime) << " seconde(s) !" << endl;
    return 0;
}
