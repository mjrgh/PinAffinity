#pragma once
#include "Util.h"

struct ProcessDesc
{
	ProcessDesc(DWORD pid, const TCHAR *name)
		: pid(pid), name(name)
	{
		key = name;
		std::transform(key.begin(), key.end(), key.begin(), ::_totlower);
	}

	// system process ID
	DWORD pid;

	// process name (usually the executable name)
	TSTRING name;

	// saved process key (lowercase exe name)
	TSTRING key;
};

bool GetProcessList(std::list<ProcessDesc> &lst);
