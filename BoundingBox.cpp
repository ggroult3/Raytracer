#include "BoundingBox.h"
#include <algorithm>

using namespace std;

BoundingBox::BoundingBox()
{

}

Vect& BoundingBox::get_maxi() {
    return maxi;
}

Vect& BoundingBox::get_mini() {
    return mini;
}

void BoundingBox::set_maxi(Vect maxVect) {
    maxi = maxVect;
}

void BoundingBox::set_maxi(double value, int i) {
    maxi[i] = value;
}

void BoundingBox::set_mini(Vect minVect) {
    mini = minVect;
}

void BoundingBox::set_mini(double value, int i) {
    mini[i] = value;
}

bool BoundingBox::intersect(Ray& r) {
    Vect& maxVect = get_maxi();
    Vect& minVect = get_mini();
    Vect& C = r.get_C();
    Vect& u = r.get_u();

    double t1x = (maxVect[0] - C[0]) / u[0];
    double t2x = (minVect[0] - C[0]) / u[0];
    double txMin = min(t1x, t2x);
    double txMax = max(t1x, t2x);

    double t1y = (maxVect[1] - C[1]) / u[1];
    double t2y = (minVect[1] - C[1]) / u[1];
    double tyMin = min(t1y, t2y);
    double tyMax = max(t1y, t2y);

    double t1z = (maxVect[2] - C[2]) / u[2];
    double t2z = (minVect[2] - C[2]) / u[2];
    double tzMin = min(t1z, t2z);
    double tzMax = max(t1z, t2z);

    double tMax = min(txMax, min(tyMax, tzMax));
    double tMin = max(txMin, max(tyMin, tzMin));

    if (tMax < 0) return false;

    return tMax > tMin;
}
