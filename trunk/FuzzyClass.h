#pragma once

#include "MFClass.h"
#include <fstream>
#include <string>
using namespace std;

class FuzzyClass
{
public:
	FuzzyClass(void);
	~FuzzyClass(void);

	//The function called by the game or application the FIS is to be used for
	//Takes the two inputs, distance from the centre line and the rate of change (delta D)
	//Returns number between -1 and 1 indicating how far left or right to turn to correct steering
	float Calculate(float D, float dD, int ReturnValue);
	float getCentroid(float Distance, float RoC);
	float getTotalArea(float Distance, float RoC);
protected:
	//Array of integers that refer to the index of each array of the MFs
	//Maps directly to the FAM for the system
	int rules[5][5];
	//Arrays to hold the individual MFs that make up the two inputs and the output
	MFClass mfsD[5], mfsDelta[5], mfsOutput[5];
	float outputHeights[5];

	void Initialise();

};