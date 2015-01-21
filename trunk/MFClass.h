#pragma once

#include <math.h>

//Struct to hold X,Y coordinates for centroid calculation
struct coord
{
	float x,y;
};

//Generic membership function class for a triangular shaped function
class MFClass
{
public:
	MFClass(void);
	MFClass(float n1, float n2, float n3);
	~MFClass(void);

	//x1, x2 and x3 hold the x positions of the membership function
	//Each is one corner of the triangle that the MF makes up
	float x1, x2, x3;
	float area;

	float GetArea(float h);
	float GetHeight(float w);
	coord GetCentroid(float h);
};