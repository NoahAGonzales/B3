#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <fstream>

using namespace cv;
using namespace std;


//What to add to GUI
//Image file selector
//Coroutine w/ loading bar
//invert image option

//Customization currently in:
// - inverting what is 255
// - height scaling
int main()
{
	double scale = 0.2;

	//Read in the image
	Mat img = imread("test9.jpg", IMREAD_GRAYSCALE);
	//Display the image
	namedWindow("image", WINDOW_FREERATIO);
	imshow("image", img);
	waitKey(0);

	//Create an array to hold the values of the pixels
	int **pixelValues = new int*[img.rows];
	for (int i = 0; i < img.rows; i++) {
		pixelValues[i] = new int[img.cols];
	}

	//Storing the values of the pixels into the values array
	for (int row = 0; row < img.rows; row++)
	{
		for (int col = 0; col < img.cols; col++) 
		{
			//int value = img.at<Vec3b>(i, j)[0];  //COLOR
			int value = img.at<uint8_t>(row, col);  //GRAYSCALE
			//White is 255
			pixelValues[row][col] = value;
			//Black is 255
			//pixelValues[row][col] = 255-value;
		}
	}

	//Creating the STL file
	ofstream picture("test.stl");
	picture << "solid pic" << endl;
	picture << endl;

	//Iterating through every other pixel 
	for (int row = 1; row < img.rows-1; row+=2)
	{
		for (int col = 1; col < img.cols-1; col+=2)
		{
			/*
			*
			* Creating facets w/ clockwise vertexes
			*
			* facet normal n1 n2 n3
			*   outer loop
			*     vertex x y z
			* 	  vertex x y z
			* 	  vertex x y z
			*   endloop
			* endfacets

			*/

			/* Top-Left
				*--*
				 \ |
				   *
			*/
			picture << "facet normal 0 0 0" << endl;
			picture << "  " << "outer loop" << endl;

			picture << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
			picture << "    " << "vertex " << row-1 << " " << col-1 << " " << pixelValues[row-1][col-1] * scale << endl;
			picture << "    " << "vertex " << row-1 << " " << col << " " << pixelValues[row-1][col] * scale << endl;

			picture << "  " << "endloop" << endl;
			picture << "endfacet" << endl;
			picture << endl;

			/* Top-Left
				*
				| \
				*--*
			*/
			picture << "facet normal 0 0 0" << endl;
			picture << "  " << "outer loop" << endl;

			picture << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
			picture << "    " << "vertex " << row << " " << col - 1 << " " << pixelValues[row][col-1] * scale << endl;
			picture << "    " << "vertex " << row - 1 << " " << col-1 << " " << pixelValues[row-1][col-1] * scale << endl;

			picture << "  " << "endloop" << endl;
			picture << "endfacet" << endl;
			picture << endl;

			/* Top-Right
				*--*
				| /
				*
			*/
			picture << "facet normal 0 0 0" << endl;
			picture << "  " << "outer loop" << endl;

			picture << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
			picture << "    " << "vertex " << row-1 << " " << col << " " << pixelValues[row-1][col] * scale << endl;
			picture << "    " << "vertex " << row - 1 << " " << col + 1 << " " << pixelValues[row - 1][col + 1] * scale << endl;

			picture << "  " << "endloop" << endl;
			picture << "endfacet" << endl;
			picture << endl;

			/* Top-Right
				   *
				 / |
				*--*
			*/
			picture << "facet normal 0 0 0" << endl;
			picture << "  " << "outer loop" << endl;

			picture << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
			picture << "    " << "vertex " << row - 1 << " " << col + 1 << " " << pixelValues[row - 1][col+1] * scale << endl;
			picture << "    " << "vertex " << row << " " << col + 1 << " " << pixelValues[row][col + 1] * scale << endl;

			picture << "  " << "endloop" << endl;
			picture << "endfacet" << endl;
			picture << endl;

			/* Bottom-Left
				   *
				 / |
				*--*
			*/
			picture << "facet normal 0 0 0" << endl;
			picture << "  " << "outer loop" << endl;

			picture << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
			picture << "    " << "vertex " << row + 1 << " " << col << " " << pixelValues[row + 1][col] * scale << endl;
			picture << "    " << "vertex " << row + 1 << " " << col - 1 << " " << pixelValues[row + 1][col - 1] * scale << endl;

			picture << "  " << "endloop" << endl;
			picture << "endfacet" << endl;
			picture << endl;

			/* Bottom-Left
				*--*
				| /
				*
			*/
			picture << "facet normal 0 0 0" << endl;
			picture << "  " << "outer loop" << endl;

			picture << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
			picture << "    " << "vertex " << row + 1 << " " << col-1 << " " << pixelValues[row + 1][col-1] * scale << endl;
			picture << "    " << "vertex " << row << " " << col - 1 << " " << pixelValues[row][col - 1] * scale << endl;

			picture << "  " << "endloop" << endl;
			picture << "endfacet" << endl;
			picture << endl;

			/* Bottom-Right
				*
				| \
				*--*
			*/
			picture << "facet normal 0 0 0" << endl;
			picture << "  " << "outer loop" << endl;

			picture << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
			picture << "    " << "vertex " << row + 1 << " " << col + 1 << " " << pixelValues[row + 1][col + 1] * scale << endl;
			picture << "    " << "vertex " << row + 1 << " " << col << " " << pixelValues[row + 1][col] * scale << endl;

			picture << "  " << "endloop" << endl;
			picture << "endfacet" << endl;
			picture << endl;

			/* Bottom-Right
				*--*
				 \ |
				   *
			*/
			picture << "facet normal 0 0 0" << endl;
			picture << "  " << "outer loop" << endl;

			picture << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
			picture << "    " << "vertex " << row << " " << col + 1 << " " << pixelValues[row][col + 1] * scale << endl;
			picture << "    " << "vertex " << row + 1 << " " << col + 1 << " " << pixelValues[row + 1][col + 1] * scale << endl;

			picture << "  " << "endloop" << endl;
			picture << "endfacet" << endl;
			picture << endl;
			
		}
	}

	picture << "endsolid pic";

	// TESTS

	//Outputting the values of the array
	/*for (int row = 0; row < img.rows; row++)
	{
		for (int col = 0; col < img.cols; col++)
		{
			cout << pixelValues[row][col] << " ";
		}
		cout << endl;
	}*/

	//ReDisplay the image (to see changes)
	/*namedWindow("output", WINDOW_FREERATIO);
	imshow("output", img);
	waitKey(0);*/

	return 0;
}