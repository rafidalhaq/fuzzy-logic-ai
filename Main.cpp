#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <math.h>
#include "FuzzyClass.h"

using namespace std;

void main()
{
	FuzzyClass fuzzy;
	bool running = true;

	//Loops the process of taking inputs and displaying the output
	while(running)
	{
		//Initialise variables
		bool loop = true;
		string input = "";
		float input1, input2;
		input1 = input2 = 2.0f;
		bool input1get = false;

		cout << "Enter Distance from line (-1 to 1): ";

		//Loops until both inputs have been entered successfully
		do
		{
			//Gets values from the console and interprets them
			getline(cin, input);
			stringstream myStream(input);
			if(!input1get)
			{
				//Check to see if what was entered can be converted to a float
				if(myStream >> input1)
				{
					//Check if the number is in the bounds -1 to 1
					if(input1 <= 1.0f && input1 >= -1.0f)
					{
						input1get = true;
						cout << "Enter rate of change (-1 to 1): ";
					}
					else cout << "Invalid number, please enter a decimal between -1 and 1.\n";
				}
				else
				{
					cout << "Invalid input, please enter a decimal number between -1 and 1.\n";
				}
			}
			else
			{
				//Checks the second input
				if(myStream >> input2)
				{
					if(input2 <= 1.0f && input2 >= -1.0f)
					{
						loop = false;
					}
					else cout << "Invalid number, please enter a decimal between -1 and 1.\n";
				}
				else
				{
					cout << "Invalid input, please enter a decimal number between -1 and 1.\n";
				}
			}
		}while(loop);
		//Once the values have been entered, the calculation is performed and the result is outputted immediately
		cout << "Input 1 = " << input1 << endl;
		cout << "Input 2 = " << input2 << endl;
		cout << "Sum of Centroids = " << fuzzy.getCentroid(input1, input2) << endl;
		cout << "Total Area = " << fuzzy.getTotalArea(input1, input2) << endl;
		cout << "Final Output = " << fuzzy.Calculate(input1,input2, 1) << "\n\n";
	}
}