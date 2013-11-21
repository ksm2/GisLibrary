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
	CSG_Grid *grid, *result;

	grid = Parameters("GRID")->asGrid();
	result = Parameters("RESULT")->asGrid();

	for (int y = 0; y < grid->Get_NY() && Set_Progress(y); y++)
	{
		for (int x = 0; x < grid->Get_NX(); x++)
		{
			int direction = Get_Flow_Direction(grid, x, y);
			result->Set_Value(x, y, direction);
		}
	}

	result->Set_Name("Flow Direction Map");

	return true;
}

//---------------------------------------------------------
// Returns the flow direction for a cell at x and y.
//---------------------------------------------------------
int CExercise_04::Get_Flow_Direction(CSG_Grid *grid, int x, int y)
{
	int result = -1;
	double resultAngle = 0;
	CSG_Grid_System system = grid->Get_System();
	double myElevation = grid->asDouble(x, y);

	for (int direction = 0; direction < 8; direction++)
	{
		int nx, ny;
		double length, nElevation, dz, angle;

		length = system.Get_Length(direction);

		// Get neighbor position
		nx = system.Get_xTo(direction, x);
		ny = system.Get_yTo(direction, y);

		if (grid->is_InGrid(nx, ny))
		{
			nElevation = grid->asDouble(nx, ny);

			dz = myElevation - nElevation;
			angle = atan(dz / length);

			if (angle > resultAngle)
			{
				result = direction;
				resultAngle = angle;
			}
		}
	}

	return result;
}

//---------------------------------------------------------
// Initializes meta information to this module.
//---------------------------------------------------------
void CExercise_04::Init_Meta_Info(void)
{
	Set_Name(_TL("Flow Accumulation"));
	Set_Author("Konstantin Simon Maria Möllers (C) 2013");
	Set_Description(_TW("Calculates the gaussian map."));
}

//---------------------------------------------------------
// Initializes the module parameters.
//---------------------------------------------------------
void CExercise_04::Init_Parameters(void)
{
	Parameters.Add_Grid(NULL, "GRID", "Grid", "...", PARAMETER_INPUT);
	Parameters.Add_Grid(NULL, "RESULT", "Result", "...", PARAMETER_OUTPUT);
}