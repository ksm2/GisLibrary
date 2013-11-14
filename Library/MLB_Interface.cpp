/**********************************************************
 * Version $Id: MLB_Interface.cpp 911 2011-11-11 11:11:11Z oconrad $
 *********************************************************/

///////////////////////////////////////////////////////////
//                                                       //
//                         SAGA                          //
//                                                       //
//      System for Automated Geoscientific Analyses      //
//                                                       //
//                    Module Library:                    //
//                       Template                        //
//                                                       //
//-------------------------------------------------------//
//                                                       //
//                   MLB_Interface.cpp                   //
//                                                       //
//                 Copyright (C) 2011 by                 //
//                     Olaf Conrad                       //
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


///////////////////////////////////////////////////////////
//														 //
//			The Module Link Library Interface			 //
//														 //
///////////////////////////////////////////////////////////

//---------------------------------------------------------
// 1. Include the appropriate SAGA-API header...
//---------------------------------------------------------
#include "MLB_Interface.h"


//---------------------------------------------------------
// 2. Place general module library informations here...
//---------------------------------------------------------
CSG_String Get_Info(int i)
{
	switch( i )
	{
	case MLB_INFO_Name:	default:
		return( _TL("M�llers Library") );

	case MLB_INFO_Author:
		return( SG_T("Konstantin Simon Maria M�llers (C) 2013") );

	case MLB_INFO_Description:
		return( _TL("M�llers's super awesome GIS Library.") );

	case MLB_INFO_Version:
		return( SG_T("1.0") );

	case MLB_INFO_Menu_Path:
		return( _TL("M�llers") );
	}
}


//---------------------------------------------------------
// 3. Include the headers of your modules here...
//---------------------------------------------------------
#include "../Modules/Template/Template.h"
#include "../Modules/Exercise_01/Exercise_01.h"


//---------------------------------------------------------
// 4. Allow your modules to be created here...
//---------------------------------------------------------
CSG_Module *Create_Module(int i)
{
	switch (i)
	{
	case  0:	return new CTemplate;
	case  1:	return new CExercise_01;

	case 11:	return NULL;
	default:	return MLB_INTERFACE_SKIP_MODULE;
	}
}

//---------------------------------------------------------
//{{AFX_SAGA

	MLB_INTERFACE

//}}AFX_SAGA
