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
//                    Exercise_02.cpp                    //
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
#include "Exercise_02.h"

//---------------------------------------------------------
// Creates the module.
//---------------------------------------------------------
CExercise_02::CExercise_02(void)
{
	this->Init_Meta_Info();
	this->Init_Parameters();
}

//---------------------------------------------------------
// Runs on module execution.
//---------------------------------------------------------
bool CExercise_02::On_Execute(void)
{
	CSG_Grid *pA, *pB, *pC;

	CSG_Parameter_Choice *pType = Parameters("TYPE")->asChoice();

	pA = Parameters("A")->asGrid();
	pB = Parameters("B")->asGrid();
	pC = Parameters("C")->asGrid();

	for (int y = 0; y < pA->Get_NY() && Set_Progress(y); y++)
	for (int x = 0; x < pA->Get_NX(); x++)
	{
		double valueA = pA->asDouble(x, y);
		double valueB = pB->asDouble(x, y);

		pC->Set_Value(x, y, Get_Value_For_Type(pType->asInt(), valueA, valueB));
	}

	pC->Set_Name(CSG_String(pType->asString()) + "-Map of " + CSG_String(pA->Get_Name()));
			
	return true;
}

//---------------------------------------------------------
// Returns the value for a given arithmetic operation.
//---------------------------------------------------------
double CExercise_02::Get_Value_For_Type(int pType, double valA, double valB)
{
	switch (pType)
	{
	case 0: return valA * valB;
	case 1: return valA / valB;
	case 2: return valA + valB;
	case 3: return valA - valB;
	}
}

//---------------------------------------------------------
// Initializes meta information to this module.
//---------------------------------------------------------
void CExercise_02::Init_Meta_Info(void)
{
	Set_Name(_TL("Exercise_02"));
	Set_Author("Konstantin Simon Maria Möllers (C) 2013");
	Set_Description(_TW("My own module description. Leik a Sir."));
}

//---------------------------------------------------------
// Initializes the module parameters.
//---------------------------------------------------------
void CExercise_02::Init_Parameters(void)
{
	Parameters.Add_Grid(
		NULL,
		"A",
		_TL("Raster A"),
		_TL("..."), PARAMETER_INPUT
		);

	Parameters.Add_Grid(
		NULL,
		"B",
		_TL("Raster B"),
		_TL("..."), PARAMETER_INPUT
		);

	Parameters.Add_Choice(NULL, "TYPE", "Operation", "Choose an operation.", "Multiplication|Division|Addition|Subtraction");

	Parameters.Add_Grid(
		NULL,
		"C",
		_TL("Raster C"),
		_TL("..."), PARAMETER_OUTPUT
		);
}