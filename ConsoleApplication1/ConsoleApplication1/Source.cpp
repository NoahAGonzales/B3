#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <fstream>

using namespace cv;
using namespace std;

int index(int x, int y, int rowLen)
{
	return (x * rowLen) + y;
}


int main()
{
	//Read in the image
	Mat img = imread("test2.jpg", IMREAD_GRAYSCALE);
	//Display the image
	namedWindow("image", WINDOW_FREERATIO);
	imshow("image", img);
	waitKey(0);

	//Create an array to hold the values of the pixels
	int **values = new int*[img.cols];
	for (int i = 0; i < img.cols; ++i) {
		values[i] = new int[img.rows];
	}

	//Storing the values of the pixels into the values array
	for (int row = 0; row < img.rows; row++)
	{
		for (int col = 0; col < img.cols; col++) 
		{
			//int value = img.at<Vec3b>(i, j)[0];  //COLOR
			int value = img.at<uint8_t>(row, col);  //GRAYSCALE
			values[row][col] = value;
			//cout << value << " ";
		}
		//cout << endl;
	}

	//Outputting the values of the array
	for (int row = 0; row < img.rows; row++)
	{
		for (int col = 0; col < img.cols; col++)
		{
			cout << values[row][col] << " ";
		}
		cout << endl;
	}

	
	//ReDisplay the image (to see changes)
	namedWindow("output", WINDOW_FREERATIO);
	imshow("output", img);
	waitKey(0);
	


	return 0;
}