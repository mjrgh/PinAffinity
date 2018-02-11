#include "stdafx.h"
#include <TlHelp32.h>
#include "ProcessList.h"

bool GetProcessList(std::list<ProcessDesc> &lst)
{
	// create a toolhelp process snapshot
	HandleHolder h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (h == 0)
		return false;

	// enumerate the processes
	PROCESSENTRY32 pe = { sizeof(pe) };
	for (BOOL ok = Process32First(h, &pe); ok; ok = Process32Next(h, &pe))
		lst.emplace_back(pe.th32ProcessID, pe.szExeFile);

	// success
	return true;
}

