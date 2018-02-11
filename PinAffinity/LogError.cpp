#include "stdafx.h"
#include "LogError.h"

void LogErrorStr(const TCHAR *msg)
{
	// just send the message to the debugger
	OutputDebugString(msg);
	OutputDebugString(_T("\n"));
}

void LogError(const TCHAR *msg, ...)
{
	// figure the required buffer space
	va_list ap;
	va_start(ap, msg);
	int l = _vsctprintf(msg, ap);
	va_end(ap);

	// if that failed, we can't format the message
	if (l < 0)
	{
		LogErrorStr(_T("Error formatting message: "));
		LogErrorStr(msg);
		LogErrorStr(_T("\n"));
		return;
	}

	// allocate the buffer
	TCHAR *buf = new TCHAR[l + 1];

	// format the message into the buffer
	va_start(ap, msg);
	_vstprintf_s(buf, l + 1, msg, ap);
	va_end(ap);

	// display it
	LogErrorStr(buf);

	// done with the buffer
	delete[] buf;
}

