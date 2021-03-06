#pragma once

#include "resource.h"
#include "SavedProcess.h"

// Process types
struct ProcTypeDesc
{
	ProcTypeDesc(const TCHAR *name, DWORD_PTR affinityMask)
		: name(name), affinityMask(affinityMask) { }

	// type name as displayed
	TSTRING name;

	// CPU affinity mask
	DWORD_PTR affinityMask;
};

// ListView item data.  Each item in the ListView keeps a pointer to
// one of these objects (allocated per list item) in its lParam field.
struct ListViewData
{
	ListViewData(DWORD pid, const TCHAR *name, const TCHAR *key, SavedProc *saved, int iType, FILETIME startTime)
		: pid(pid), name(name), key(key), saved(saved), iType(iType),
		startTime(startTime), processDeleted(false)
	{
		effPid = saved != 0 ? -1 : pid;
	}

	// get the ListViewData object for a row in the list view
	static ListViewData *FromRow(int iRow);

	// get the select row and its ListViewData object
	static ListViewData *GetSelectedRow()
	{
		int iRow;
		return GetSelectedRow(iRow);
	}
	static ListViewData *GetSelectedRow(int &iRow);

	// PID of the associated process
	DWORD pid;

	// effective PID for sorting: -1 if it's a non-process saved item, so
	// that these sort ahead of all processes when sorting by PID
	DWORD effPid;

	// process name
	TSTRING name;

	// process name sort key
	TSTRING key;

	// special process type
	int iType;

	// starting time
	FILETIME startTime;

	// Placeholder saved process item.  We create placeholder
	// entries in the list for all saved processes that aren't
	// currently running.  The placeholder items are identified
	// by a pointer here.
	SavedProc *saved;

	// Process deleted flag.  When the associated ProcListItem is
	// destroyed, it sets this flag to let us know to remove the
	// corresponding list item.
	bool processDeleted;
};

// Process list entry
struct ProcListItem
{
	ProcListItem(DWORD pid, const TCHAR *name, const TCHAR *key, DWORD updated,
		DWORD_PTR origAffinity, DWORD_PTR newAffinity, DWORD_PTR sysAffinity,
		FILETIME startTime)
		: pid(pid), name(name), key(key), updated(updated),
		origAffinity(origAffinity), newAffinity(newAffinity), sysAffinity(sysAffinity),
		dirty(false), lvd(NULL), startTime(startTime)
	{ }

	// the entry is dirty - it's been modified since the last UI update
	bool dirty;

	// process ID
	DWORD pid;

	// Original process affinity mask
	DWORD_PTR origAffinity;

	// System affinity mask
	DWORD_PTR sysAffinity;

	// New affinity mask after our update
	DWORD_PTR newAffinity;

	// process name
	TSTRING name;

	// saved process key
	TSTRING key;

	// process creation time
	FILETIME startTime;

	// update iteration counter
	DWORD updated;

	// The List View Data object for this process
	ListViewData *lvd;
};


