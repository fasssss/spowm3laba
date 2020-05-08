#include<windows.h>
#include<iostream>

using namespace std;

int main()
{
	HANDLE sem1 = OpenSemaphore(EVENT_ALL_ACCESS, FALSE, "1stReady");
	HANDLE map = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "Share");
	HANDLE sem2 = OpenSemaphore(EVENT_ALL_ACCESS, FALSE, "2thReady");
	char* a =(char*) MapViewOfFile(map, FILE_MAP_ALL_ACCESS, 0, 0, 100);
	WaitForSingleObject(sem1, INFINITE);
	CloseHandle(map);
	cout << "transfered\n";
	cout << a;
	UnmapViewOfFile(a);
	cout << endl;
	system("pause");
	ReleaseSemaphore(sem2, 1, NULL);
	CloseHandle(sem1);
	CloseHandle(sem2);
	return 0;
}