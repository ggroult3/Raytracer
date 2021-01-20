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

    int W = 512;
    int H = 512;
    /*
    Vect C(0,0,55);
    Vect O(0,0,0);
    double R = 10;
    Sphere S(O,R);
    double fov = 60 * M_PI / 180;
    */
    vector<unsigned char> image(W*H * 3,0);
    for (int i = 0 ; i < H; i++){
        for (int j = 0 ; j < W ; j++){
            //Vect u(j - W / 2,i - H / 2, - W / (2.*tan(fov/2)));
            //Ray r(C,u);

            image[(i*W+j) * 3 + 0] = 255;
            image[(i*W+j) * 3 + 1] = 0;
            image[(i*W+j) * 3 + 2] = 0;
        }
    }

    stbi_write_png("image_hello_world.png",W,H,3,&image[0],0);

    time(&endTime);
    cout << "Cela dure " << difftime(endTime,beginTime) << " seconde(s) !" << endl;
    return 0;
}
