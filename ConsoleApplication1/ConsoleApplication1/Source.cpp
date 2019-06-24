#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <fstream>

using namespace cv;
using namespace std;

void writeFacetBeginning(ofstream&);
void writeFacetEnd(ofstream&);



//What to add to GUI
//Image file selector
//Coroutine w/ loading bar
//invert image option

//Customization currently in:
// - inverting what is 255
// - height scaling


int main()
{
	double scale = 0.1;

	//Rea kd in the image
	Mat img = imread("test12.jpg", IMREAD_GRAYSCALE);
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
	ofstream stl("test.stl");
	stl << "solid pic" << endl;
	stl << endl;

	/*
	* Iterating through every other pixel to generate the facets of the top face
	*
	*                * -- * -- *
	*                |  \ | /  |
	*                * -- * -- *
	*                |  / | \  |
	*                * -- * -- *
	*
	*/

	for (int row = 1; row < img.rows; row+=2)
	{
		for (int col = 1; col < img.cols; col+=2)
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
			writeFacetBeginning(stl);
			stl << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
			stl << "    " << "vertex " << row - 1 << " " << col << " " << pixelValues[row - 1][col] * scale << endl;
			stl << "    " << "vertex " << row-1 << " " << col-1 << " " << pixelValues[row-1][col-1] * scale << endl;
			writeFacetEnd(stl);

			/* Top-Left
				*
				| \
				*--*
			*/
			writeFacetBeginning(stl);
			stl << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
			stl << "    " << "vertex " << row - 1 << " " << col - 1 << " " << pixelValues[row - 1][col - 1] * scale << endl;
			stl << "    " << "vertex " << row << " " << col - 1 << " " << pixelValues[row][col-1] * scale << endl;
			writeFacetEnd(stl);

			/* Top-Right
				*--*
				| /
				*
			*/
			if (col+1 < img.cols) //Is this pixel not on the last column
			{
				writeFacetBeginning(stl);
				stl << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
				stl << "    " << "vertex " << row - 1 << " " << col + 1 << " " << pixelValues[row - 1][col + 1] * scale << endl;
				stl << "    " << "vertex " << row - 1 << " " << col << " " << pixelValues[row - 1][col] * scale << endl;
				writeFacetEnd(stl);

				/* Top-Right
					   *
					 / |
					*--*
				*/
				writeFacetBeginning(stl);
				stl << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
				stl << "    " << "vertex " << row << " " << col + 1 << " " << pixelValues[row][col + 1] * scale << endl;
				stl << "    " << "vertex " << row - 1 << " " << col + 1 << " " << pixelValues[row - 1][col + 1] * scale << endl;
				writeFacetEnd(stl);
			}

			if (row + 1 < img.rows) //Is this pixel not on the last row?
			{
				/* Bottom-Left
					   *
					 / |
					*--*
				*/
				writeFacetBeginning(stl);
				stl << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
				stl << "    " << "vertex " << row + 1 << " " << col - 1 << " " << pixelValues[row + 1][col - 1] * scale << endl;
				stl << "    " << "vertex " << row + 1 << " " << col << " " << pixelValues[row + 1][col] * scale << endl;
				writeFacetEnd(stl);

				/* Bottom-Left
					*--*
					| /
					*
				*/
				writeFacetBeginning(stl);
				stl << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
				stl << "    " << "vertex " << row << " " << col - 1 << " " << pixelValues[row][col - 1] * scale << endl;
				stl << "    " << "vertex " << row + 1 << " " << col - 1 << " " << pixelValues[row + 1][col - 1] * scale << endl;
				writeFacetEnd(stl);
			}

			if (row + 1 < img.rows && col + 1 < img.cols)
			{
				/* Bottom-Right
					*
					| \
					*--*
				*/
				writeFacetBeginning(stl);
				stl << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
				stl << "    " << "vertex " << row + 1 << " " << col << " " << pixelValues[row + 1][col] * scale << endl;
				stl << "    " << "vertex " << row + 1 << " " << col + 1 << " " << pixelValues[row + 1][col + 1] * scale << endl;
				writeFacetEnd(stl);

				/* Bottom-Right
					*--*
					 \ |
					   *
				*/
				writeFacetBeginning(stl);
				stl << "    " << "vertex " << row << " " << col << " " << pixelValues[row][col] * scale << endl;
				stl << "    " << "vertex " << row + 1 << " " << col + 1 << " " << pixelValues[row + 1][col + 1] * scale << endl;
				stl << "    " << "vertex " << row << " " << col + 1 << " " << pixelValues[row][col + 1] * scale << endl;
				writeFacetEnd(stl);
			}
			
		}
	}

	/*
	* Creating initial triangles for corners (side and bottom) if need be to avoid condition checking for each pixel along the edge
	*/
	double centerX = (img.cols-1) / 2.0;
	double centerY = (img.rows-1) / 2.0;

	//Top-left corner
	if (pixelValues[0][0] != 0)
	{
		/*
		* Sides
		*/

		//Left edge going across rows
		writeFacetBeginning(stl);
		stl << "    " << "vertex " << 0 << " " << 0 << " " << pixelValues[0][0] * scale << endl;
		stl << "    " << "vertex " << 0 << " " << 0 << " " << 0 << endl;
		stl << "    " << "vertex " << 1 << " " << 0 << " " << 0 << endl;
		writeFacetEnd(stl);

		//Top edge going across columns
		writeFacetBeginning(stl);
		stl << "    " << "vertex " << 0 << " " << 0 << " " << pixelValues[0][0] * scale << endl;
		stl << "    " << "vertex " << 0 << " " << 1 << " " << 0 << endl;
		stl << "    " << "vertex " << 0 << " " << 0 << " " << 0 << endl;
		writeFacetEnd(stl);

		/*
		* Bottom
		*/

		//Left edge going across rows
		writeFacetBeginning(stl);
		stl << "    " << "vertex " << 0 << " " << 0 << " " << 0 << endl;
		stl << "    " << "vertex " << centerX << " " << centerY << " " << 0 << endl;
		stl << "    " << "vertex " << 1 << " " << 0 << " " << 0 << endl;
		writeFacetEnd(stl);

		//Top edge going across columns
		writeFacetBeginning(stl);
		stl << "    " << "vertex " << 0 << " " << 0 << " " << 0 << endl;
		stl << "    " << "vertex " << 0 << " " << 1 << " " << 0 << endl;
		stl << "    " << "vertex " << centerX << " " << centerY << " " << 0 << endl;
		writeFacetEnd(stl);
	}
	
	//Bottom-Left corner
	if (pixelValues[img.rows-1][0] != 0)
	{
		/*
		* Sides
		*/

		//Left edge going across rows
		writeFacetBeginning(stl);
		stl << "    " << "vertex " << img.rows - 1 << " " << 0 << " " << pixelValues[img.rows - 1][0] * scale << endl;
		stl << "    " << "vertex " << img.rows - 2 << " " << 0 << " " << pixelValues[img.rows - 1][0] * scale << endl;
		stl << "    " << "vertex " << img.rows - 1 << " " << 0 << " " << 0 << endl;
		writeFacetEnd(stl);

		//Bottom edge going across columns
		writeFacetBeginning(stl);
		stl << "    " << "vertex " << img.rows - 1 << " " << 0 << " " << pixelValues[img.rows - 1][0] * scale << endl;
		stl << "    " << "vertex " << img.rows - 1 << " " << 0 << " " << 0 << endl;
		stl << "    " << "vertex " << img.rows - 1 << " " << 1 << " " << 0 << endl;
		writeFacetEnd(stl);

		/*
		* Bottom
		*/

		//Bottom edge going across columns
		writeFacetBeginning(stl);
		stl << "    " << "vertex " << img.rows - 1 << " " << 0 << " " << 0 << endl;
		stl << "    " << "vertex " << centerX << " " << centerY << " " << 0 << endl;
		stl << "    " << "vertex " << img.rows - 1 << " " << 1 << " " << 0 << endl;
		writeFacetEnd(stl);
	}
	
	//Top-right corner
	if (pixelValues[0][img.cols-1] != 0)
	{
		/*
		* Sides
		*/

		//Top edge going across columns
		writeFacetBeginning(stl);
		stl << "    " << "vertex " << 0 << " " << img.cols-1 << " " << pixelValues[0][img.cols-1] * scale << endl;
		stl << "    " << "vertex " << 0 << " " << img.cols - 1 << " " << 0 << endl;
		stl << "    " << "vertex " << 0 << " " << img.cols-2 << " " << pixelValues[0][img.cols-2] * scale << endl;
		writeFacetEnd(stl);
		
		//Right edge going across rows
		writeFacetBeginning(stl);
		stl << "    " << "vertex " << 0 << " " << img.cols - 1 << " " << pixelValues[0][img.cols - 1] * scale << endl;
		stl << "    " << "vertex " << 1 << " " << img.cols - 1 << " " << 0 << endl;
		stl << "    " << "vertex " << 0 << " " << img.cols - 1 << " " << 0 << endl;
		writeFacetEnd(stl);
		
		/*
		* Bottom
		*/

		//Right edge going across rows
		writeFacetBeginning(stl);
		stl << "    " << "vertex " << 0 << " " << img.cols - 1 << " " << 0 << endl;
		stl << "    " << "vertex " << 1 << " " << img.cols - 1 << " " << 0 << endl;
		stl << "    " << "vertex " << centerX << " " << centerY << " " << 0 << endl;
		writeFacetEnd(stl);
	}
	//Bottom-right corner
	if (pixelValues[img.rows-1][img.cols - 1] != 0)
	{
		/*
		* Sides
		*/

		//Right edge going across rows
		writeFacetBeginning(stl);
		stl << "    " << "vertex " << img.rows-1 << " " << img.cols - 1 << " " << pixelValues[img.rows-1][img.cols - 1] * scale << endl;
		stl << "    " << "vertex " << img.rows-1 << " " << img.cols - 1 << " " << 0 << endl;
		stl << "    " << "vertex " << img.rows-2 << " " << img.cols - 1 << " " << pixelValues[img.rows-2][img.cols-1] * scale<< endl;
		writeFacetEnd(stl);

		//Bottom edge going across columns
		writeFacetBeginning(stl);
		stl << "    " << "vertex " << img.rows-1 << " " << img.cols - 1 << " " << pixelValues[img.rows-1][img.cols - 1] * scale << endl;
		stl << "    " << "vertex " << img.rows - 1 << " " << img.cols - 2 << " " << pixelValues[img.rows - 1][img.cols - 2] * scale << endl;
		stl << "    " << "vertex " << img.rows-1 << " " << img.cols - 1 << " " << 0 << endl;
		writeFacetEnd(stl);
	}


	//Creating the base. Every pixel along the edge except the first and last will be used to create 2 facets. Facet 1 consits of the point, the point changed to a value of zero, and the last point. Facet 2 consists of the point, the next point changed to a value of zero, and the point changed to a value of 0;
	for (int row = 1; row < img.rows-1; row++)
	{
		//Left edge
		if (pixelValues[row][0] != 0)
		{
			/*
			* Sides
			*/
			writeFacetBeginning(stl);
			stl << "    " << "vertex " << row << " " << 0 << " " << pixelValues[row][0] * scale << endl;
			stl << "    " << "vertex " << row - 1 << " " << 0 << " " << pixelValues[row - 1][0] * scale << endl;
			stl << "    " << "vertex " << row << " " << 0 << " " << 0 << endl;
			writeFacetEnd(stl);

			writeFacetBeginning(stl);
			stl << "    " << "vertex " << row << " " << 0 << " " << pixelValues[row][0] * scale << endl;
			stl << "    " << "vertex " << row << " " << 0 << " " << 0 << endl;
			stl << "    " << "vertex " << row+1 << " " << 0 << " " << 0 << endl;
			writeFacetEnd(stl);

			/*
			* Bottom
			*/
			writeFacetBeginning(stl);
			stl << "    " << "vertex " << row << " " << 0 << " " << 0 << endl;
			stl << "    " << "vertex " << centerX << " " << centerY << " " << 0 << endl;
			stl << "    " << "vertex " << row+1 << " " << 0 << " " << 0 << endl;
			writeFacetEnd(stl);
		}
		//Right edge
		if (pixelValues[row][img.cols-1] != 0)
		{
			/*
			* Sides
			*/
			writeFacetBeginning(stl);
			stl << "    " << "vertex " << row << " " << img.cols-1 << " " << pixelValues[row][img.cols-1] * scale << endl;
			stl << "    " << "vertex " << row << " " << img.cols-1 << " " << 0 << endl;
			stl << "    " << "vertex " << row - 1 << " " << img.cols-1 << " " << pixelValues[row-1][img.cols-1] * scale << endl;
			writeFacetEnd(stl);

			writeFacetBeginning(stl);
			stl << "    " << "vertex " << row << " " << img.cols-1 << " " << pixelValues[row][img.cols-1] * scale << endl;
			stl << "    " << "vertex " << row+1 << " " << img.cols-1 << " " << 0 << endl;
			stl << "    " << "vertex " << row << " " << img.cols-1 << " " << 0 << endl;
			writeFacetEnd(stl);

			/*
			* Bottom
			*/
			writeFacetBeginning(stl);
			stl << "    " << "vertex " << row << " " << img.cols-1 << " " << 0 << endl;
			stl << "    " << "vertex " << row + 1 << " " << img.cols - 1 << " " << 0 << endl;
			stl << "    " << "vertex " << centerX << " " << centerY << " " << 0 << endl;
			writeFacetEnd(stl);
		}
	}
	for (int col = 1; col < img.cols - 1; col++)
	{
		//Top edge
		if (pixelValues[0][col] != 0)
		{
			/*
			* Sides
			*/
			writeFacetBeginning(stl);
			stl << "    " << "vertex " << 0 << " " << col << " " << pixelValues[0][col] * scale << endl;
			stl << "    " << "vertex " << 0 << " " << col << " " << 0 << endl;
			stl << "    " << "vertex " << 0 << " " << col-1 << " " << pixelValues[0][col-1] * scale << endl;
			writeFacetEnd(stl);

			writeFacetBeginning(stl);
			stl << "    " << "vertex " << 0 << " " << col << " " << pixelValues[0][col] * scale << endl;
			stl << "    " << "vertex " << 0 << " " << col+1 << " " << 0 << endl;
			stl << "    " << "vertex " << 0 << " " << col << " " << 0 << endl;
			writeFacetEnd(stl);

			/*
			* Bottom
			*/
			writeFacetBeginning(stl);
			stl << "    " << "vertex " << 0 << " " << col << " " << 0 << endl;
			stl << "    " << "vertex " << 0 << " " << col + 1 << " " << 0 << endl;
			stl << "    " << "vertex " << centerX << " " << centerY << " " << 0 << endl;
			writeFacetEnd(stl);
		}
		//Bottom edge
		if (pixelValues[img.rows-1][col] != 0)
		{
			/*
			* Sides
			*/
			writeFacetBeginning(stl);
			stl << "    " << "vertex " << img.rows-1 << " " << col << " " << pixelValues[img.rows-1][col] * scale << endl;
			stl << "    " << "vertex " << img.rows - 1 << " " << col - 1 << " " << pixelValues[img.rows - 1][col - 1] * scale << endl;
			stl << "    " << "vertex " << img.rows-1 << " " << col << " " << 0 << endl;
			writeFacetEnd(stl);

			writeFacetBeginning(stl);
			stl << "    " << "vertex " << img.rows-1 << " " << col << " " << pixelValues[img.rows-1][col] * scale << endl;
			stl << "    " << "vertex " << img.rows - 1 << " " << col << " " << 0 << endl;
			stl << "    " << "vertex " << img.rows-1 << " " << col + 1 << " " << 0 << endl;
			writeFacetEnd(stl);

			/*
			* Bottom
			*/
			writeFacetBeginning(stl);
			stl << "    " << "vertex " << img.rows-1 << " " << col << " " << 0 << endl;
			stl << "    " << "vertex " << centerX << " " << centerY << " " << 0 << endl;
			stl << "    " << "vertex " << img.rows-1 << " " << col + 1 << " " << 0 << endl;
			writeFacetEnd(stl);
		}
	}

	stl << "endsolid pic";
	stl.close();

	return 0;
}

void writeFacetBeginning(ofstream &stl)
{
	stl << "facet normal 0 0 0" << endl;
	stl << "  " << "outer loop" << endl;
}

void writeFacetEnd(ofstream &stl)
{
	stl << "  " << "endloop" << endl;
	stl << "endfacet" << endl;
	stl << endl;
}