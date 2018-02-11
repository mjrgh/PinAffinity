#include "stdafx.h"
#include "TrayAnimation.h"

#define DEFAULT_RECT_WIDTH 150
#define DEFAULT_RECT_HEIGHT 30

static void GetTrayRect(RECT &rc)
{
	// look for a window of class Shell_TrayWnd
	HWND hShellTrayWnd = FindWindowEx(NULL, NULL, _T("Shell_TrayWnd"), NULL);
	if (hShellTrayWnd != 0)
	{
		// got it - find the tray notification window
		HWND hTrayNotifyWnd = FindWindowEx(hShellTrayWnd, NULL, _T("TrayNotifyWnd"), NULL);
		if (hTrayNotifyWnd != 0)
		{
			// use its rectangle
			GetWindowRect(hTrayNotifyWnd, &rc);
			return;
		}
	}

	// We didn't find the window by class - maybe we're on a newer Windows
	// version where they've changed the internals.  Look for the taskbar
	// by asking the shell which window edge the taskbar is attached to,
	// then figure the taskbar area as an approximate area near that edge.
	// Note that this doesn't tell us the exact size, but for the purposes
	// of the minimize/restore animations, we don't really need the exact
	// size; an approximation will do fine.
	APPBARDATA appBarData;
	appBarData.cbSize = sizeof(appBarData);
	if (SHAppBarMessage(ABM_GETTASKBARPOS, &appBarData))
	{
		// success - guess the rect based on the window edge
		switch (appBarData.uEdge)
		{
		case ABE_LEFT:
		case ABE_RIGHT:
			// We want to minimize to the bottom of the taskbar
			rc.top = appBarData.rc.bottom - 100;
			rc.bottom = appBarData.rc.bottom - 16;
			rc.left = appBarData.rc.left;
			rc.right = appBarData.rc.right;
			break;

		case ABE_TOP:
		case ABE_BOTTOM:
			// We want to minimize to the right of the taskbar
			rc.top = appBarData.rc.top;
			rc.bottom = appBarData.rc.bottom;
			rc.left = appBarData.rc.right - 100;
			rc.right = appBarData.rc.right - 16;
			break;
		}

		return;
	}

	// That didn't even work.  There might be a third-party shell running.
	// See if they provided the Shell_TrayWnd class, at least, and if so
	// just assume the tray is at the bottom.
	hShellTrayWnd = FindWindowEx(NULL, NULL, _T("Shell_TrayWnd"), NULL);
	if (hShellTrayWnd)
	{
		GetWindowRect(hShellTrayWnd, &rc);
		if (rc.right - rc.left > DEFAULT_RECT_WIDTH)
			rc.left = rc.right - DEFAULT_RECT_WIDTH;
		if (rc.bottom - rc.top > DEFAULT_RECT_HEIGHT)
			rc.top = rc.bottom - DEFAULT_RECT_HEIGHT;

		return;
	}

	// We didn't find anything to go on.  Use a default based on the
	// desktop work area, guessing that the tray is at the bottom.
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
	rc.left = rc.right - DEFAULT_RECT_WIDTH;
	rc.top = rc.bottom - DEFAULT_RECT_HEIGHT;
}

// Check to see if the animation has been disabled
static BOOL GetDoAnimateMinimize(VOID)
{
	ANIMATIONINFO ai;
	ai.cbSize = sizeof(ai);
	SystemParametersInfo(SPI_GETANIMATION, sizeof(ai), &ai, 0);

	return ai.iMinAnimate ? TRUE : FALSE;
}

void MinimizeToTray(HWND hWnd)
{
	ShowWindow(hWnd, SW_MINIMIZE);
	return;//$$$


	if (GetDoAnimateMinimize())
	{
		RECT rcFrom, rcTo;

		// Get the rect of the window. It is safe to use the rect of the whole
		// window - DrawAnimatedRects will only draw the caption
		GetWindowRect(hWnd, &rcFrom);
		GetTrayRect(rcTo);

		// Get the system to draw our animation for us
		DrawAnimatedRects(hWnd, IDANI_CAPTION, &rcFrom, &rcTo);
	}

	// Hide the window
	ShowWindow(hWnd, SW_HIDE);
}

void RestoreFromTray(HWND hWnd)
{
	if (GetDoAnimateMinimize())
	{
		// Get the rect of the tray and the window. Note that the window rect
		// is still valid even though the window is hidden
		RECT rcFrom, rcTo;
		GetTrayRect(rcFrom);
		GetWindowRect(hWnd, &rcTo);

		// Get the system to draw our animation for us
		DrawAnimatedRects(hWnd, IDANI_CAPTION, &rcFrom, &rcTo);
	}

	// Show the window, and make sure we're the foreground window
	ShowWindow(hWnd, SW_SHOW);
	SetActiveWindow(hWnd);
	SetForegroundWindow(hWnd);
}
