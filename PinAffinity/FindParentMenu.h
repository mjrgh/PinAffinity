#pragma once

// Find the immediate parent menu of the given command,  searching
// recursively through the given menu's submenu tree.
HMENU FindParentMenu(HMENU hMenu, UINT id);
