// CriticalMutex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"


void testing()
{
	HANDLE mutex = CreateMutex(NULL, FALSE, L"teste");
	CRITICAL_SECTION critSec;
	InitializeCriticalSection(&critSec);

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	LARGE_INTEGER start, end;

	// Force code into memory, so we don't see any effects of paging.
	EnterCriticalSection(&critSec);
	LeaveCriticalSection(&critSec);
	QueryPerformanceCounter(&start);
	for (int i = 0; i < 1000000; i++)
	{
		EnterCriticalSection(&critSec);
		LeaveCriticalSection(&critSec);
	}

	QueryPerformanceCounter(&end);

	int totalTimeCS = (int)((end.QuadPart - start.QuadPart) * 1000 / freq.QuadPart);

	// Force code into memory, so we don't see any effects of paging.
	WaitForSingleObject(mutex, INFINITE);
	ReleaseMutex(mutex);

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 1000000; i++)
	{
		WaitForSingleObject(mutex, INFINITE);
		ReleaseMutex(mutex);
	}

	QueryPerformanceCounter(&end);

	int totalTime = (int)((end.QuadPart - start.QuadPart) * 1000 / freq.QuadPart);

	printf("Mutex: %d CritSec: %d\n", totalTime, totalTimeCS);
}

int _tmain(int argc, _TCHAR* argv[])
{
	testing();
	getchar();
	return 0;
}

