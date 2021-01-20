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

Vect operator+(const Vect& a, const Vect& b){
    return Vect(a[0] + b[0],a[1] + b[1],a[2] + b[2]);
}

Vect operator-(const Vect& a, const Vect& b){
    return Vect(a[0] - b[0],a[1] - b[1],a[2] - b[2]);
}

Vect operator-(const Vect& a){
    return Vect(-a[0],-a[1],-a[2]);
}

Vect operator*(const Vect& a, double b){
    return Vect(a[0]*b,a[1]*b,a[2]*b);
}

Vect operator*(double a,const Vect& b){
    return Vect(a*b[0],a*b[1],a*b[2]);
}

Vect operator/(const Vect& a, double b){
    return Vect(a[0]/b,a[1]/b,a[2]/b);
}

double dot(const Vect& a,const Vect& b){
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

double sqr(double x){
    return x*x;
}

int main()
{
    time_t beginTime,endTime;
    time(&beginTime);
    cout << "beginTime = " << beginTime << endl;
    cout << "Hello World!" << endl;

    Vect v(0.,2.,3.);
    Vect w(9.,8.,7.);
    Ray r(v,w);

    cout << "R.C = (" << r.get_C()[0] << "," << r.get_C()[1] << "," << r.get_C()[2] << ")" << endl;

    cin.get();

    cout << "Norme de u = " << sqrt(r.get_u().sqrNorm()) << endl;
    time(&endTime);
    cout << "endTime = " << endTime << endl;
    cout << "Cela dure " << difftime(endTime,beginTime) << " secondes !" << endl;
    return 0;
}
