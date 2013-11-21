///////////////////////////////////////////////////////////
//                                                       //
//                         SAGA                          //
//                                                       //
//      System for Automated Geoscientific Analyses      //
//                                                       //
//                    Module Library:                    //
//                        Möllers                        //
//                                                       //
//-------------------------------------------------------//
//                                                       //
//                    Exercise_04.cpp                    //
//                                                       //
//                 Copyright (C) 2013 by                 //
//            Konstantin Simon Maria Möllers             //
//                                                       //
//-------------------------------------------------------//
//                                                       //
// This file is part of 'SAGA - System for Automated     //
// Geoscientific Analyses'. SAGA is free software; you   //
// can redistribute it and/or modify it under the terms  //
// of the GNU General Public License as published by the //
// Free Software Foundation; version 2 of the License.   //
//                                                       //
// SAGA is distributed in the hope that it will be       //
// useful, but WITHOUT ANY WARRANTY; without even the    //
// implied warranty of MERCHANTABILITY or FITNESS FOR A  //
// PARTICULAR PURPOSE. See the GNU General Public        //
// License for more details.                             //
//                                                       //
// You should have received a copy of the GNU General    //
// Public License along with this program; if not,       //
// write to the Free Software Foundation, Inc.,          //
// 59 Temple Place - Suite 330, Boston, MA 02111-1307,   //
// USA.                                                  //
//                                                       //
//-------------------------------------------------------//
//                                                       //
//    e-mail:     oconrad@saga-gis.de                    //
//                                                       //
//    contact:    Olaf Conrad                            //
//                Institute of Geography                 //
//                University of Hamburg                  //
//                Germany                                //
//                                                       //
///////////////////////////////////////////////////////////

//---------------------------------------------------------
#include "Exercise_04.h"
#include <math.h>

//---------------------------------------------------------
// Creates the module.
//---------------------------------------------------------
CExercise_04::CExercise_04(void)
{
	this->Init_Meta_Info();
	this->Init_Parameters();
}

//---------------------------------------------------------
// Runs on module execution.
//---------------------------------------------------------
bool CExercise_04::On_Execute(void)
{
	CSG_Grid *result;

	inputGrid = Parameters("GRID")->asGrid();
	result = Parameters("RESULT")->asGrid();

	radius = Parameters("SIZE")->asInt();

	// Reserve memory for the matrix
	double *gaussMatrix = (double *) malloc(sizeof(double) * (4 * radius * radius + 4 * radius + 1));
	Calc_Gauss_Matrix(gaussMatrix);

	for (int y = 0; y < inputGrid->Get_NY() && Set_Progress(y); y++)
	{
		for (int x = 0; x < inputGrid->Get_NX(); x++)
		{
			double value = Get_Mean(x, y, gaussMatrix);
			result->Set_Value(x, y, value);
		}
	}
	result->Set_Name("Gaussian Map");		

	// Free the matrix
	free(gaussMatrix);

	return true;
}

//---------------------------------------------------------
// Initializes meta information to this module.
//---------------------------------------------------------
void CExercise_04::Init_Meta_Info(void)
{
	Set_Name(_TL("Gaußscher Weichzeichner"));
	Set_Author("Konstantin Simon Maria Möllers (C) 2013");
	Set_Description(_TW("Calculates the gaussian map."));
}

//---------------------------------------------------------
// Initializes the module parameters.
//---------------------------------------------------------
void CExercise_04::Init_Parameters(void)
{
	Parameters.Add_Grid(NULL, "GRID", "Grid", "...", PARAMETER_INPUT);
	Parameters.Add_Value(NULL, "SIZE", "Größe der Umgebung", "...", PARAMETER_TYPE_Int, 3.0);
	Parameters.Add_Grid(NULL, "RESULT", "Result", "...", PARAMETER_OUTPUT);
}

//---------------------------------------------------------
// Get the mean value around x and y.
//---------------------------------------------------------
double CExercise_04::Get_Mean(int x, int y, double *matrix)
{
	double value = 0;
	double *relMatrix = matrix;

	for (int i = -radius; i < radius; i++)
	{
		for (int j = -radius; j < radius; j++)
		{
			// Get relative coordinates
			int myX = x - j;
			int myY = y - i;

			// Ensure x is in grid
			if (myX < 0)
				myX = 0;
			else if (myX >= inputGrid->Get_NX())
				myX = inputGrid->Get_NX() - 1;

			// Ensure y is in grid
			if (myY < 0)
				myY = 0;
			else if (myY >= inputGrid->Get_NY())
				myY = inputGrid->Get_NY() - 1;

			// Get the value

			double factor = *relMatrix;
			value += factor * inputGrid->asDouble(myX, myY);

			relMatrix++;
		}
	}

	return value;
}

//---------------------------------------------------------
// Calculate the gauss matrix.
//---------------------------------------------------------
void CExercise_04::Calc_Gauss_Matrix(double *matrix)
{
	double coeff = 1 / sqrt(2 * M_PI);
	for (int x = 0; x < 2 * radius + 1; x++)
	{
		double *xptrLeft = matrix + (x * (2 * radius + 1)) + radius;
		double *xptrRight = xptrLeft;
		double xsqr = radius + 1 - x;
		xsqr *= xsqr;

		for (int y = 0; y <= radius; y++)
		{
			int ysqr = y * y;
			double distancesqr = xsqr + ysqr;
			distancesqr = distancesqr / (radius * radius) * 4;
			double gauss = coeff * exp(-0.5 * distancesqr);

			*xptrLeft = gauss;
			*xptrRight = gauss;

			xptrLeft--;
			xptrRight++;
		}
	}
}