// CancelarSeguroClub.h: archivo de encabezado principal para la aplicaci�n PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	//#error incluye 'stdafx.h' antes de incluir este archivo para PCH
#endif

#include "resource.h"		// S�mbolos principales
#include "ctrlglob.hpp"

// CCancelarSeguroClubApp:
// Consulte la secci�n CancelarSeguroClub.cpp para obtener informaci�n sobre la implementaci�n de esta clase
//

class CCancelarSeguroClubApp : public CWinApp
{
public:
	CCancelarSeguroClubApp();

// Reemplazos
	public:
	virtual BOOL InitInstance();

// Implementaci�n

	DECLARE_MESSAGE_MAP()
};

extern CCancelarSeguroClubApp theApp;
