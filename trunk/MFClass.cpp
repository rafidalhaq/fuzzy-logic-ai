#include "MFClass.h"

MFClass::MFClass(void)
{

}

MFClass::MFClass(float n1, float n2, float n3)
{
	//Sets the coordinates
	x1 = n1;
	x2 = n2;
	x3 = n3;

	//Calculates full area of the MF for later use
	if(x3 > 1)
	{
		area = (x2-x1)/2;
	}
	else if(x1 < -1)
	{
		area = (x3-x2)/2;
	}
	else area = (x2-x1)/2+(x3-x2)/2;
}

MFClass::~MFClass(void)
{

}

float MFClass::GetArea(float h)
{
	//Returns the total area of the membership function below the height "h"
	float scale = 1 - h;
	float newArea;
	if(x3 > 1)
	{
		newArea = (scale*scale*(x2-x1))/2;
	}
	else if(x1 < -1)
	{
		newArea = (scale*scale*(x3-x2))/2;
	}
	else newArea = (scale*scale*(x2-x1))/2+(scale*scale*(x3-x2)/2);

	return area - newArea;
}

float MFClass::GetHeight(float w)
{
	//-- Checks if the given x-coordinate lies within the bounds of the MF
	//-- And returns the height along the MF at that point if it does
	if(w > x1 && w < x2)
	{
		float width = abs(x2 - x1);
		float width2 = abs(x2 - w);
		return 1-width2/width;
	}
	else if(w >= x2 && w <= x3)
	{
		float width = abs(x3 - x2);
		float width2 = abs(w - x2);
		return 1-width2/width;
	}
	else return 0;
}

coord MFClass::GetCentroid(float h)
{
	//-- Calculates the average centroid of the two triangles and rectangle
	//-- that make up the MF
	float scale = 1 - h;

	//-- Special case for outer membership functions
	if(x3 > 1.05f)
	{
		//-- Calculate centroid of triangle on the left
		float w2 = abs(x1 - 1);
		coord cent2;
		cent2.x = x2 - w2/3;
		cent2.y = h/3;
		return cent2;
	}
	else if(x1 < -1.05f)
	{		
		//-- Calculate centroid of triangle on the right
		float w3 = abs(x3 - -1);
		coord cent3;
		cent3.x = x2 + w3/3;
		cent3.y = h/3;
		return cent3;
	}

	//-- Calculate width of centre rectangle, if 0 it is ignored later
	float w1 = (scale*(x2-x1)) + (scale*(x3-x2));
	//-- Calculate centroid of the rectangle
	coord cent1;
	if(abs(x2 - x1) > abs(x3 - x2))
	{
		cent1.x = (x2 - scale*(x2-x1)) + w1/2;
	}
	else
	{
		cent1.x = (x2 + scale*(x3-x2)) - w1/2;
	}
	cent1.y = scale/2;
	
	//-- Calculate centroid of triangle on the left
	float w2 = abs(x1 - (cent1.x - w1/2));
	coord cent2;
	cent2.x = (cent1.x - w1/2) - w2/3;
	cent2.y = h/3;

	//-- Calculate centroid of triangle on the right
	float w3 = abs(x3 - (cent1.x + w1/2));
	coord cent3;
	cent3.x = (cent1.x + w1/2) + w3/3;
	cent3.y = h/3;

	//-- Combine the three (or two) centroids to find the mid point
	coord cent;
	if(h < 1.0f)
	{
		cent.x = (cent1.x + cent2.x + cent3.x)/3;
		cent.y = (cent1.y + cent2.y + cent3.y)/3;
	}
	else
	{
		cent.x = (cent2.x + cent3.x)/2;
		cent.y = (cent2.y + cent3.y)/2;
	}
	return cent;
}