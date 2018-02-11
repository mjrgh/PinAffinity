#pragma once

// array element count
#define countof(array) (sizeof(array)/sizeof((array)[0]))

// TCHAR string type
typedef std::basic_string<TCHAR> TSTRING;

// Handle closer.  This is a simple RAII object that closes a handle
// upon going out of scope.
struct HandleHolder
{
	HandleHolder() : h(NULL) { }
	HandleHolder(HANDLE h) : h(h) { }
	~HandleHolder() { if (h != NULL) CloseHandle(h); }
	HANDLE h;

	operator HANDLE() { return h; }
	HANDLE* operator&() { return &h; }
	void operator=(HANDLE h) {
		if (this->h != NULL) CloseHandle(this->h);
		this->h = h;
	}
};

