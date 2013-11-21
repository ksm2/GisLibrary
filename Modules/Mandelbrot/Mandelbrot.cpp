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
//                    Mandelbrot.cpp                     //
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
#include "Mandelbrot.h"

//---------------------------------------------------------
// Creates the module.
//---------------------------------------------------------
CMandelbrot::CMandelbrot(void)
{
	this->Init_Meta_Info();
	this->Init_Parameters();
}

//---------------------------------------------------------
// Runs on module execution.
//---------------------------------------------------------
bool CMandelbrot::On_Execute(void)
{
	CSG_Grid *result;
	result = Parameters("RESULT")->asGrid();

	Draw_Mandelbrot(result);

	result->Set_Name("Mandelbrot Fraktal");
			
	return true;
}

//---------------------------------------------------------
// Initializes meta information to this module.
//---------------------------------------------------------
void CMandelbrot::Init_Meta_Info(void)
{
	Set_Name(_TL("Mandelbrot-Fraktal"));
	Set_Author("Konstantin Simon Maria Möllers (C) 2013");
	Set_Description(_TW("Das Apfelmännchen."));
}

//---------------------------------------------------------
// Initializes the module parameters.
//---------------------------------------------------------
void CMandelbrot::Init_Parameters(void)
{
	Parameters.Add_Grid(NULL, "RESULT", "Result", "...", PARAMETER_OUTPUT);
}

//---------------------------------------------------------
// The Mandelbrot algorithm.
//---------------------------------------------------------
void CMandelbrot::Draw_Mandelbrot(CSG_Grid *grid)
{
	int centerX, centerY;
	double scale;

	centerX = grid->Get_NX() / 2;
	centerY = grid->Get_NY() / 2;

	scale = grid->Get_NY() * 0.4;

	for (int y = 0; y < grid->Get_NY() && Set_Progress(y); y++)
	{
		for (int x = 0; x < grid->Get_NX(); x++)
		{
			int iterations = 0;
			double re = 0;
			double im = 0;
			double xre = (x - centerX) / scale - .4;
			double yim = (y - centerY) / scale;
			do
			{
				double newRe, newIm;
				newRe = re * re - im * im + xre;
				newIm = 2 * re * im + yim;

				re = newRe;
				im = newIm;

				iterations++;
			} while (iterations < 500 && In_Circle(re, im));

			grid->Set_Value(x, y, iterations);
		}
	}
}

//---------------------------------------------------------
// Finds out, if x and y are in the circle.
//---------------------------------------------------------
bool CMandelbrot::In_Circle(double re, int im)
{
	return re * re + im * im <= 4;
}