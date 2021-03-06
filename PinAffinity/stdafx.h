// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// use XP-compatible process API
#define DSAPI_VERSION 1

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <Windows.h>
#include <commdlg.h>
#include <CommCtrl.h>
#include <Psapi.h>
#include <Shlwapi.h>
#include <shellapi.h>
#include <VersionHelpers.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <varargs.h>
#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

// TODO: reference additional headers your program requires here
