// winget.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Urlmon.h"

struct arguments {
	_TCHAR* option;
	_TCHAR* description;
	_TCHAR* parameter;
	unsigned int required;
};

struct arguments help, download;

void CreateArgs(){
	help.option = _T("-h");
	help.description = _T("show this help");
	help.required = 0;
	download.option = _T("-d");
	download.description = _T("the URL to be downloaded");
	download.required = 1;
}

bool getFile(TCHAR* filename, TCHAR* URL)
{
	HRESULT result = URLDownloadToFile(NULL,URL,filename,0,NULL);
	switch(result)
	{
		case E_OUTOFMEMORY: return FALSE; break;
		case INET_E_DOWNLOAD_FAILURE: return FALSE; break;
		case S_OK: return TRUE; break;
		default: return FALSE; break;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	CreateArgs();
	if (argc <= 2) {
		_tprintf(L"Usage:\n\n");
		_tprintf(L"Parameter \"%s\" %s\n", help.option, help.description);
		_tprintf(L"Parameter \"%s\" %s\n", download.option, download.description);
	} else {
		for (int i=0; i < argc; i++)
		{
			if ((argv[i][0] == help.option[0]) && (argv[i][1] == help.option[1]))
			{
				_tprintf(L"Parameter \"%s\" %s\n", help.option, help.description);
			}
			else if ((argv[i][0] == download.option[0]) && (argv[i][1] == download.option[1]))
			{
				getFile(L"page.html", argv[i+1]);
			}
		}.
		return 0;
	}
}