// MasterEvent.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"

void IpcThread(int lpParam)
{
	HANDLE ghRequestEvent = NULL ;

	ghRequestEvent = CreateEvent(NULL, FALSE,
	FALSE, L"Global\\Event1") ; //creating the event

	if(NULL == ghRequestEvent)
	{
		//error
		wprintf(L"Falha ao criar event object\n");
	}
	int cont = 0;
	while(cont < lpParam)
	{
		//waiting for the event
		WaitForSingleObject(ghRequestEvent, INFINITE);
		//here some action related to event
		cont++;
		// O Uso do sleep prova que se receber dois eventos consecutivos o sistema processa os dois
		Sleep(10000);
		wprintf(L"Recebido evento %d de %d\n", cont, lpParam);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	IpcThread(3);
	return 0;
}

