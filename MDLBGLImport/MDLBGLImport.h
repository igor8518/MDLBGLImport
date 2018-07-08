#pragma once
#include "3dsmaxsdk_preinclude.h"
#include <istdplug.h>
#include <iparamb2.h>
#include <iparamm2.h>
#include <maxtypes.h>
#include <triobj.h>
#include <impapi.h>

//SIMPLE TYPE


#include <impexp.h>
#include <direct.h>
#include <commdlg.h>
#include <stdmat.h>

class MDLBGLImport
{
public:
	int DoImport(const TCHAR* filename, ImpInterface* i, Interface* gi, BOOL suppressPrompts);
};
