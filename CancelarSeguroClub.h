// CancelarSeguroClub.h: archivo de encabezado principal para la aplicación PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	//#error incluye 'stdafx.h' antes de incluir este archivo para PCH
#endif

#include "resource.h"		// Símbolos principales
#include "ctrlglob.hpp"

// CCancelarSeguroClubApp:
// Consulte la sección CancelarSeguroClub.cpp para obtener información sobre la implementación de esta clase
//

class CCancelarSeguroClubApp : public CWinApp
{
public:
	CCancelarSeguroClubApp();

// Reemplazos
	public:
	virtual BOOL InitInstance();

// Implementación

	DECLARE_MESSAGE_MAP()
};

extern CCancelarSeguroClubApp theApp;
