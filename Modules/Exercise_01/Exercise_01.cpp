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
	Set_Name		(_TL("Exercise_01"));

	Set_Author		("Konstantin Simon Maria Möllers (C) 2013");

	Set_Description	(_TW(
		"My own module description. Leik a Sir."
	));

	Parameters.Add_String(
		NULL	, "TEXT"	, _TL("Text"),
		_TL(""),
		"Hello World"
	);

	Parameters.Add_Value(
		NULL	, "VALUE"	, _TL("Value"),
		_TL(""),
		PARAMETER_TYPE_Double, M_PI
	);
}

//---------------------------------------------------------
// Runs on module execution.
//---------------------------------------------------------
bool CExercise_01::On_Execute(void)
{
	CSG_String	Text;

	Text.Printf(SG_T("%s\n\n%s: %f"), Parameters("TEXT")->asString(), _TL("Value"), Parameters("VALUE")->asDouble());

	Message_Dlg(Text);

	return( true );
}
