#pragma once
#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#define _CRT_SECURE_NO_WARNINGS 1

#include <string>
#include <list>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include "Vect.h"
#include "TriangleIndices.h"
#include "Ray.h"
#include "Object.h"
#include "BoundingBox.h"
#include "Noeud.h"
#include "stb_image.h"

using namespace std;


class TriangleMesh : public Object {
public:
    ~TriangleMesh();
    TriangleMesh(const Vect& albedo, bool mirror, bool transp);
    TriangleMesh(const Vect& albedo, bool mirror);
    TriangleMesh(const Vect& albedo);

    //void buildBB();
    BoundingBox buildBB(int debut, int fin);
    int buildBVH(Noeud* n, int debut, int fin);

    void readOBJ(const char* obj);

    bool intersect(Ray& r, Vect& P, Vect& N, double& t,Vect& color);

    Vect& get_albedo();
    bool& get_isMirror();
    bool& get_isTransp();

    void loadTexture(const char* filename);

    vector<TriangleIndices> indices;
    vector<Vect> vertices;
    vector<Vect> normals;
    vector<Vect> uvs;
    vector<Vect> vertexcolors;
    vector<unsigned char*> textures;
    vector<int> Wtex, Htex;
    Noeud* BVH;
    BoundingBox bb;

private:
    Vect albedo;
    bool isMirror;
    bool isTransp;
    

};

#endif // TRIANGLEMESH_H
