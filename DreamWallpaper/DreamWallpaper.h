
// DreamWallpaper.h: arquivo de cabeçalho principal para o aplicativo PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "inclua 'pch.h' antes de incluir este arquivo para PCH"
#endif

#include "resource.h"		// símbolos principais


// CDreamWallpaperApp:
// Consulte DreamWallpaper.cpp para a implementação desta classe
//

class CDreamWallpaperApp : public CWinApp
{
public:
	CDreamWallpaperApp();

// Substitui
public:
	virtual BOOL InitInstance();

// Implementação

	DECLARE_MESSAGE_MAP()
};

extern CDreamWallpaperApp theApp;
