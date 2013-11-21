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
//                     Exercise_04.h                     //
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
#ifndef HEADER_INCLUDED__Exercise_04_H
#define HEADER_INCLUDED__Exercise_04_H

//---------------------------------------------------------
#include "../../Library/MLB_Interface.h"

//---------------------------------------------------------
// The Template Module class.
//---------------------------------------------------------
class CExercise_04 : public CSG_Module_Grid
{
public:
	CExercise_04(void);

protected:
	virtual bool On_Execute(void);

private:
	CSG_Grid *inputGrid;
	int radius;

	void Init_Meta_Info(void);
	void Init_Parameters(void);
	double Get_Mean(int x, int y, double *matrix);
	void Calc_Gauss_Matrix(double *matrix);
};

//---------------------------------------------------------
#endif // #ifndef HEADER_INCLUDED__Exercise_04_H
