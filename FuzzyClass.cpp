#include "FuzzyClass.h"
#include <iostream>
FuzzyClass::FuzzyClass(void)
{
	//-- Loads in all values needed directly from the .fis file
	Initialise();
}

FuzzyClass::~FuzzyClass(void)
{

}

float FuzzyClass::Calculate(float Distance, float RoC, int ReturnValue)
{
	coord sumCentroid; sumCentroid.x = sumCentroid.y = 0;
	for(int i = 0; i < 5; i++) outputHeights[i] = 0;
	float totalArea = 0;
	//-- Check each MF combination to see if the input values lie within them
	//-- For each MF for the Distance input
	for(int i = 0; i < 5; i++)
	{
		float height1 = mfsD[i].GetHeight(Distance);
		//If the distance lies within the bounds of that MF, proceed to find MFs for the other input
		if(height1 > 0)
		{
			//For each MF for the Rate of Change input
			for(int j = 0; j < 5; j++)
			{
				float height2 = mfsDelta[j].GetHeight(RoC);
				//If the RoC lies within the bounds of that MF
				if(height2 > 0)
				{
					//Determine minimum height between the two inputs
					float outputHeight;
					if(height1 > height2) outputHeight = height2;
					else outputHeight = height1;
					
					if(outputHeight > outputHeights[rules[i][j]])
					{
						//Gets the centroid at the minimum height against the appropriate rule
						//Determines which output MF to use by passing the qualifying input MF indices
						//into the rules array which acts as a look up table matching the FAM of the system
						coord centroid = mfsOutput[rules[i][j]].GetCentroid(outputHeight);
						//Gets the area of the output, multiplies the centroid by it and adds it to the total
						float area = mfsOutput[rules[i][j]].GetArea(outputHeight);
						sumCentroid.x += centroid.x*area;
						sumCentroid.y += centroid.y*area;
						totalArea += area;
						outputHeights[rules[i][j]] = outputHeight;
					}
				}
			}	
		}
	}
	//Once all MFs have been checked, the sum of all centroids is divided by
	//the total area of the output to deffuzzify the result
	float result = sumCentroid.x/totalArea;
	switch (ReturnValue)
	{
		case 1:
			return result;
			break;
		case 2:
			return sumCentroid.x;
		    break;
		case 3:
			return totalArea;
			break;
		default:
			std::cout << "Error: Invalid Parameter";
			break;
	}
	
		
	

}

float FuzzyClass::getCentroid(float Distance, float RoC)
{
	return Calculate(Distance, RoC, 2);
}
float FuzzyClass::getTotalArea(float Distance, float RoC)
{
	return Calculate(Distance, RoC, 3);
}
void FuzzyClass::Initialise()
{
	//Loads in the inputs, outputs and rules from the .fis file generated in MATLAB
	string line;
	ifstream myfile ("fuzzy.fis");
	if(myfile.is_open())
	{
		bool loop = true;
		do
		{
			string input;
			getline(myfile, input);

			//Starts reading from the headers for each section
			if(input == "[Input1]")
			{
				for(int i = 0; i < 3; i++) getline(myfile, input);
				for(int i = 0; i < 5; i++)
				{
					getline(myfile, input);
					int pos = input.find_first_of("[")+1;
					int newpos;

					float coords[3];
					for(int j = 0; j < 3; j++)
					{
						newpos =  input.find_first_of(" ", pos);
						int len = newpos - pos;
						
						string num = input.substr(pos,len);
						coords[j] = atof(num.c_str());
						pos = newpos+1;
					}
					mfsD[i] = MFClass(coords[0],coords[1],coords[2]);
				}
			}
			else if(input == "[Input2]")
			{
				for(int i = 0; i < 3; i++) getline(myfile, input);
				for(int i = 0; i < 5; i++)
				{
					getline(myfile, input);
					int pos = input.find_first_of("[")+1;
					int newpos;

					float coords[3];
					for(int j = 0; j < 3; j++)
					{
						newpos =  input.find_first_of(" ", pos);
						int len = newpos - pos;
						
						string num = input.substr(pos,len);
						coords[j] = atof(num.c_str());
						pos = newpos+1;
					}
					mfsDelta[i] = MFClass(coords[0],coords[1],coords[2]);
				}
			}
			else if(input == "[Output1]")
			{
				for(int i = 0; i < 3; i++) getline(myfile, input);
				for(int i = 0; i < 5; i++)
				{
					getline(myfile, input);
					int pos = input.find_first_of("[")+1;
					int newpos;

					float coords[3];
					for(int j = 0; j < 3; j++)
					{
						newpos =  input.find_first_of(" ", pos);
						int len = newpos - pos;
						
						string num = input.substr(pos,len);
						coords[j] = atof(num.c_str());
						pos = newpos+1;
					}
					mfsOutput[i] = MFClass(coords[0],coords[1],coords[2]);
				}
			}
			//Loads in the rules and stores them in an array
			else if(input == "[Rules]")
			{
				loop = false;
				for(int i = 0; i < 25; i++)
				{
					getline(myfile, input);
					int x = atoi((input.substr(0,1)).c_str());
					int y = atoi((input.substr(2,1)).c_str());
					int output = atoi((input.substr(5,1)).c_str());
					rules[x-1][y-1] = output-1;
				}
			} 
		}
		while(loop);

		myfile.close();
	}
}