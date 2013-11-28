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
//                    Exercise_06.cpp                    //
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
#include "Exercise_06.h"
#include <math.h>
#include <time.h>
#include <windows.h>

//---------------------------------------------------------
// Creates the module.
//---------------------------------------------------------
CExercise_06::CExercise_06(void)
{
	this->Init_Meta_Info();
	this->Init_Parameters();
}

//---------------------------------------------------------
// Runs on module execution.
//---------------------------------------------------------
bool CExercise_06::On_Execute(void)
{
	CSG_Grid *grid;

	int nx = Parameters("NX")->asInt();
	int ny = Parameters("NY")->asInt();
	int sleep = Parameters("SLEEP")->asInt();

	grid = Create_Random_Grid(nx, ny);

	while (Process_Get_Okay())
	{
		//Sleep(sleep);
		
		CSG_Grid *newGrid = new CSG_Grid(grid);

		#pragma omp parallel for
		for (int x = 0; x < nx; x++)
		{
			for (int y = 0; y < ny; y++)
			{
				int newValue = Find_New_Value_For_Cell(grid, x, y, nx, ny);
				newGrid->Set_Value(x, y, newValue);
			}
		}

		*grid = *newGrid;
		DataObject_Update(grid, 1);
	}

	return true;
}

//---------------------------------------------------------
// Creates a random grid for the game of life.
//---------------------------------------------------------
int CExercise_06::Find_New_Value_For_Cell(CSG_Grid *grid, int x, int y, int nx, int ny)
{
	int neighbors = 0;
	CSG_Grid_System system = grid->Get_System();
	
	for (int direction = 0; direction < 8; direction++)
	{
		int myx = (system.Get_xTo(direction, x) + nx) % nx;
		int myy = (system.Get_yTo(direction, y) + ny) % ny;

		neighbors += grid->asInt(myx, myy) - 1;
	}

	return Get_Game_Of_Life_Rule(grid->asInt(x, y) - 1, neighbors);
}

//---------------------------------------------------------
// Applies Conways Rule for the game of life.
//---------------------------------------------------------
int CExercise_06::Get_Game_Of_Life_Rule(bool isAlive, int neighbors)
{
	if (isAlive)
	{
		if (neighbors < 2 || neighbors > 3)
			return 1;
	}
	else
	{
		if (neighbors == 3)
			return 2;
	}
	return isAlive + 1;
}

//---------------------------------------------------------
// Creates a random grid for the game of life.
//---------------------------------------------------------
CSG_Grid *CExercise_06::Create_Random_Grid(int nx, int ny)
{
	CSG_Grid *lifeGrid = SG_Create_Grid(SG_DATATYPE_Byte, nx, ny);
	lifeGrid->Set_Name("Life");

	DataObject_Add(lifeGrid);
	DataObject_Set_Colors(lifeGrid, CSG_Colors(2, SG_COLORS_YELLOW_BLUE, true));

	srand(time(NULL));

	for (int x = 0; x < nx; x++)
	{
		for (int y = 0; y < ny; y++)
		{
			int random = rand() % 2 + 1;
			lifeGrid->Set_Value(x, y, random);
		}
	}

	return lifeGrid;
}

//---------------------------------------------------------
// Initializes meta information to this module.
//---------------------------------------------------------
void CExercise_06::Init_Meta_Info(void)
{
	Set_Name(_TL("Game of Life"));
	Set_Author("Konstantin Simon Maria Möllers (C) 2013");
	Set_Description(_TW("Calculates the game of life."));
}

//---------------------------------------------------------
// Initializes the module parameters.
//---------------------------------------------------------
void CExercise_06::Init_Parameters(void)
{
	Parameters.Add_Value(NULL, "NX", "Width", "Game of life width", PARAMETER_TYPE_Int, 100, 10);
	Parameters.Add_Value(NULL, "NY", "Height", "Game of life height", PARAMETER_TYPE_Int, 100, 10);
	Parameters.Add_Value(NULL, "SLEEP", "Sleep", "Time between life cycles", PARAMETER_TYPE_Int, 100, 10);
}