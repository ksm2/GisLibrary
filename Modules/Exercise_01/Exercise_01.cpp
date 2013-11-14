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
//                    Exercise_01.cpp                    //
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
#include "Exercise_01.h"

//---------------------------------------------------------
// Creates the module.
//---------------------------------------------------------
CExercise_01::CExercise_01(void)
{
	this->Init_Meta_Info();
	this->Init_Parameters();
}

//---------------------------------------------------------
// Runs on module execution.
//---------------------------------------------------------
bool CExercise_01::On_Execute(void)
{
	CSG_Grid *pInput	= Parameters("INPUT")->asGrid();
	CSG_Grid *pCopy		= Parameters("COPY")->asGrid();

	pCopy->Assign(pInput);

	return true;
}

//---------------------------------------------------------
// Initializes meta information to this module.
//---------------------------------------------------------
void CExercise_01::Init_Meta_Info(void)
{
	Set_Name(_TL("Exercise_01"));
	Set_Author("Konstantin Simon Maria Möllers (C) 2013");
	Set_Description(_TW("My own module description. Leik a Sir."));
}

//---------------------------------------------------------
// Initializes the module parameters.
//---------------------------------------------------------
void CExercise_01::Init_Parameters(void)
{
	Parameters.Add_Grid(
		NULL,
		"INPUT",
		_TL("Raster to be copied"),
		_TL("The original raster, which will be copied."), PARAMETER_INPUT
		);

	Parameters.Add_Grid(
		NULL,
		"COPY",
		_TL("This is the copy"),
		_TL("The copied raster."), PARAMETER_OUTPUT
		);
}