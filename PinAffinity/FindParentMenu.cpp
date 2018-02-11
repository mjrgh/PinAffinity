#include "stdafx.h"
#include "FindParentMenu.h"

// does the given menu contain an item with the given ID?
static bool MenuContainsID(HMENU hMenu, UINT id)
{
	// scan the menu for an item with the given ID
	MENUITEMINFO mf;
	mf.cbSize = sizeof(mf);
	mf.fMask = MIIM_ID;
	for (int pos = GetMenuItemCount(hMenu); --pos >= 0; )
	{
		// return true if this is the item we're looking for
		if (GetMenuItemInfo(hMenu, (UINT)pos, TRUE, &mf) && mf.wID == id)
			return true;
	}

	// didn't find it
	return false;
}

// check if the given item is a submenu
static HMENU GetSubmenu(HMENU hMenu, UINT pos)
{
	// get the menu item's submenu to see if it has one
	MENUITEMINFO mf;
	mf.cbSize = sizeof(mf);
	mf.fMask = MIIM_SUBMENU;
	if (GetMenuItemInfo(hMenu, pos, TRUE, &mf))
		return mf.hSubMenu;

	// couldn't get the menu item info -> no submenu to return
	return 0;
}

// Find the submenu within a menu tree that contains the given command item
HMENU FindParentMenu(HMENU hMenu, UINT id)
{
	// scan each item in this menu
	for (int pos = GetMenuItemCount(hMenu); --pos >= 0; ) 
	{
		// get this item's submenu, if it has one
		HMENU hSubMenu = GetSubMenu(hMenu, (UINT)pos);
		if (hSubMenu != 0)
		{
			// check if the submenu contains the item we're seeking
			if (MenuContainsID(hSubMenu, id))
				return hSubMenu;

			// it's not an immediate child; recursively search into the submenu
			if ((hSubMenu = FindParentMenu(hSubMenu, id)) != 0)
				return hSubMenu;
		}
	}

	// not found
	return 0;
}
