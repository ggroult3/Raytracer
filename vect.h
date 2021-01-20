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
    friend Vect operator+(const Vect& a, const Vect& b);
    friend Vect operator-(const Vect& a, const Vect& b);
    friend Vect operator-(const Vect& a);
    friend Vect operator*(const Vect& a, double b);
    friend Vect operator*(double a,const Vect& b);
    friend Vect operator/(const Vect& a, double b);
    friend double dot(const Vect& a,const Vect& b);
    friend double sqr(double x);

private:
    double coords[3];

};

#endif // VECT_H
