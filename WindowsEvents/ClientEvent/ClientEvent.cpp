// ClientEvent.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"

unsigned int event_notification()
{
	HANDLE ghRequestEvent = NULL ;
	ghRequestEvent = OpenEvent(SYNCHRONIZE|EVENT_MODIFY_STATE, FALSE, L"Global\\Event1") ;
	if(NULL == ghRequestEvent)
	{
	//error
	wprintf(L"Falha ao abrir event object\n");
	}
	SetEvent(ghRequestEvent);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	event_notification();
	return 0;
}

