//
//	ShellExecute() sample, like "open" command in Mac OS X.
//
//	see also... http://msdn.microsoft.com/ja-jp/library/cc422072.aspx
//

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <shellapi.h>

void usage()
{
	::MessageBox(NULL, _T("usage: open.exe [filenames]"), _T("usage"), MB_OK);
	exit(1);
}

void error(TCHAR *filename)
{
	TCHAR msg[MAX_PATH + 256];
	_stprintf_s(msg, MAX_PATH + 256, _T("can't open file. filename=%s"), filename);
	::MessageBox(NULL, msg, _T("error"), MB_OK);
	exit(1);
}

bool open(TCHAR *filename)
{
	HINSTANCE h;

	h = ::ShellExecute(NULL, _T("open"), filename, NULL, NULL, SW_SHOW);
	if ((int)h <= 32) {
		return false;
	}
	return true;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	bool rv;
	int  i;

	if (__argc == 1) usage();

	for (i = 1; i < __argc; ++i) {
		rv = open(__targv[i]);
		if (!rv) {
			error(__targv[i]);
			exit(1);
		}
	}
	
	return 0;
}
