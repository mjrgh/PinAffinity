#pragma once
#include "Util.h"

// Saved process list item
struct SavedProc
{
	SavedProc(const TCHAR *name, int iType) 
		: name(name), iType(iType), numInstances(0), inListView(false) 
	{
		key = name;
		std::transform(key.begin(), key.end(), key.begin(), ::_totlower);
		dirty = false;
	}

	// process name
	TSTRING name;

	// process name key (lowercase version of name)
	TSTRING key;

	// number of running instances
	int numInstances;

	// special program type code
	int iType;

	// do I have a ListView placeholder entry?
	bool inListView;

	// does the UI element need to be updated for a change?
	bool dirty;
};

