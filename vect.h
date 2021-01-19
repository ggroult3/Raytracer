#ifndef VECT_H
#define VECT_H


class Vect
{
public:
    explicit Vect(double x=0,double y=0,double z=0);
    double operator[](int i) const;
    double &operator[](int i);
    double sqrNorm();
    Vect get_normalized();

private:
    double coords[3];

};

#endif // VECT_H
