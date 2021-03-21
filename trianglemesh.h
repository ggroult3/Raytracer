#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include <string>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <vect.h>
#include <triangleindices.h>
#include <ray.h>
#include <object.h>

using namespace std;


class TriangleMesh : public Object {
public:
  ~TriangleMesh();
    TriangleMesh(const Vect& albedo,bool mirror, bool transp);
    TriangleMesh(const Vect& albedo,bool mirror);
    TriangleMesh(const Vect& albedo);

    void readOBJ(const char* obj);

    bool intersect(Ray& r, Vect& P,Vect& N,double& t);

    Vect& get_albedo();
    bool& get_isMirror();
    bool& get_isTransp();

    vector<TriangleIndices> indices;
    vector<Vect> vertices;
    vector<Vect> normals;
    vector<Vect> uvs;
    vector<Vect> vertexcolors;

private:
    Vect albedo;
    bool isMirror;
    bool isTransp;

};

#endif // TRIANGLEMESH_H
