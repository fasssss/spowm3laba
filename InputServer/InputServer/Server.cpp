#include<windows.h>
#include<iostream>

using namespace std;

int main()
{
	HANDLE file = CreateFile("buffer.txt", FILE_ALL_ACCESS, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE sem = OpenSemaphore(EVENT_ALL_ACCESS, FALSE, "Ready");
	HANDLE sem2 = CreateSemaphore(NULL, 0, 1, "2thReady");
	HANDLE sem1 = CreateSemaphore(NULL, 0, 1, "1stReady");
	HANDLE map = CreateFileMapping(file, NULL, PAGE_READWRITE, 0, 100, "Share");
	char* a =(char*) MapViewOfFile(map, FILE_MAP_ALL_ACCESS, 0, 0, 100);
	ReleaseSemaphore(sem, 1, NULL);
	cout << "enter your word" << endl;
	cin >> a;
	ReleaseSemaphore(sem1, 1, NULL);
	WaitForSingleObject(sem2, INFINITE);
	UnmapViewOfFile(a);
	CloseHandle(file);
	CloseHandle(map);
	system("pause");
	return 0;
}