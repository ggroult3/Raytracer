#pragma once
#include "BoundingBox.h"
class Noeud
{
public:
	Noeud* fg, * fd;
	BoundingBox b;
	int debut, fin;
};

