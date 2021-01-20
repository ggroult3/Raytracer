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
    cout << "beginTime = " << beginTime << endl;
    cout << "Hello World!" << endl;

    Vect v(0.,0.,0.);
    Vect w(1.,0.,0.);
    Ray r(v,w);

    Vect O(0.,20.,0.);
    double R = 10;
    Sphere s(O,R);

    cout << "Ray d'origine C(" << r.get_C()[0] << "," << r.get_C()[1] << "," << r.get_C()[2] << ")" << endl;
    cout << "et de direction u(" << r.get_u()[0] << "," << r.get_u()[1] << "," << r.get_u()[2] << ")" << endl;

    cin.get();

    cout << "Sphere de rayon " << s.get_R() << " et de centre O("<< s.get_O()[0] << "," << s.get_O()[1] << "," << s.get_O()[2] << ")" << endl;

    cin.get();

    bool result = s.intersect(r);
    string response;

    if (result){
        response = "Oui";
    }
    else{
        response = "Non";
    }

    cout << "Intersection Sphere-Ray ? : " << response << endl;

    cin.get();

    Vect O2(20.,0.,0.);
    double R2 = 10;
    Sphere s2(O2,R2);

    cout << "Sphere de rayon " << s2.get_R() << " et de centre O("<< s2.get_O()[0] << "," << s2.get_O()[1] << "," << s2.get_O()[2] << ")" << endl;

    cin.get();

    result = s2.intersect(r);

    if (result){
        response = "Oui";
    }
    else{
        response = "Non";
    }

    cout << "Intersection Sphere-Ray ? : " << response << endl;

    cin.get();

    Vect O3(0.,20.,0.);
    double R3 = 50;
    Sphere s3(O3,R3);

    cout << "Sphere de rayon " << s3.get_R() << " et de centre O("<< s3.get_O()[0] << "," << s3.get_O()[1] << "," << s3.get_O()[2] << ")" << endl;

    cin.get();

    result = s3.intersect(r);

    if (result){
        response = "Oui";
    }
    else{
        response = "Non";
    }

    cout << "Intersection Sphere-Ray ? : " << response << endl;

    cin.get();

    time(&endTime);
    cout << "endTime = " << endTime << endl;
    cout << "Cela dure " << difftime(endTime,beginTime) << " secondes !" << endl;
    return 0;
}
