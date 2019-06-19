// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include 

int main()
{
    std::cout << "Hello World!\n"; 

	Mat pic = imread("circle.jpg", IMREAD_GRAYSCALE);

	ofstream log;
	log.open("log.txt");


	for (int r = 0; r < pic.rows; r++)
	{
		for (int c = 0; c < pic.cols; c++)
		{

			log << pic.at<uint8_t>(r, c);
			log << " ";
		}
		log << endl;
	}

	log.close();
	namedWindow("Picture", WINDOW_AUTOSIZE);
	imshow("Picture", pic);
	waitKey(0);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
