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
//                    Exercise_03.cpp                    //
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
#include "Exercise_03.h"

//---------------------------------------------------------
// Creates the module.
//---------------------------------------------------------
CExercise_03::CExercise_03(void)
{
	this->Init_Meta_Info();
	this->Init_Parameters();
}

//---------------------------------------------------------
// Runs on module execution.
//---------------------------------------------------------
bool CExercise_03::On_Execute(void)
{
	CSG_Grid *grid, *result;

	grid = Parameters("GRID")->asGrid();
	result = Parameters("RESULT")->asGrid();

	int size = Parameters("SIZE")->asInt();

	for (int y = 0; y < grid->Get_NY() && Set_Progress(y); y++)
	for (int x = 0; x < grid->Get_NX(); x++)
	{
		double value = 0;

		for (int i = -size; i < size; i++)
		for (int j = -size; j < size; j++) 
		{
			int myX = x - j;
			int myY = y - i;

			if (myX < 0)
				myX = 0;
			else if (myX >= grid->Get_NX())
				myX = grid->Get_NX() - 1;

			if (myY < 0)
				myY = 0;
			else if (myY >= grid->Get_NY())
				myY = grid->Get_NY() - 1;
		
			value += grid->asDouble(myX, myY);
		}

		value /= size * size;

		result->Set_Value(x, y, value);
	}

	result->Set_Name("Antialiased Map");
			
	return true;
}

//---------------------------------------------------------
// Initializes meta information to this module.
//---------------------------------------------------------
void CExercise_03::Init_Meta_Info(void)
{
	Set_Name(_TL("Nachbarschaftsrenderer"));
	Set_Author("Konstantin Simon Maria Möllers (C) 2013");
	Set_Description(_TW("My own module description. Leik a Sir."));
}

//---------------------------------------------------------
// Initializes the module parameters.
//---------------------------------------------------------
void CExercise_03::Init_Parameters(void)
{
	Parameters.Add_Grid(NULL, "GRID", "Grid", "...", PARAMETER_INPUT);
	Parameters.Add_Value(NULL, "SIZE", "Größe der Umgebung", "...", PARAMETER_TYPE_Int, 3.0);
	Parameters.Add_Grid(NULL, "RESULT", "Result", "...", PARAMETER_OUTPUT);
}