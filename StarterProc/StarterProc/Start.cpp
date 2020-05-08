#include<windows.h>
#include<iostream>

using namespace std;

int main()
{
	PROCESS_INFORMATION PrInf1;
	STARTUPINFO StInf1 = { sizeof(StInf1) };
	PROCESS_INFORMATION PrInf2;
	STARTUPINFO StInf2 = { sizeof(StInf2) };
	HANDLE sem = CreateSemaphore(NULL, 0, 1, "Ready");
	CreateProcess("C:\\Users\\we\\source\\repos\\labs 4 sem\\Spowm_3_lab\\InputServer\\Debug\\InputServer.exe"
		, NULL
		, NULL
		, NULL
		, TRUE
		, CREATE_NEW_CONSOLE
		, NULL
		, NULL
		, &StInf1
		, &PrInf1);
	WaitForSingleObject(sem, INFINITE);
	CreateProcess("C:\\Users\\we\\source\\repos\\labs 4 sem\\Spowm_3_lab\\OutputClient\\Debug\\OutputClient.exe"
		, NULL
		, NULL
		, NULL
		, TRUE
		, CREATE_NEW_CONSOLE
		, NULL
		, NULL
		, &StInf2
		, &PrInf2);
	cout << "enter smth to clouse" << endl;
	system("pause");
	HANDLE hPrInf[2] = { PrInf1.hProcess, PrInf2.hProcess };
	WaitForMultipleObjects(2, hPrInf, TRUE, INFINITE);
	CloseHandle(PrInf1.hProcess);
	CloseHandle(PrInf1.hThread);
	CloseHandle(PrInf2.hProcess);
	CloseHandle(PrInf2.hThread);
	return 0;
}