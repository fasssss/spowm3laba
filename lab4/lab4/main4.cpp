#include<iostream>
#include<windows.h>
#include<conio.h>

using namespace std; 
CRITICAL_SECTION mute;
int n = 0, j = 1;
DWORD WINAPI Thread_1(LPVOID t) {
	while (true) {
		if (n == 0)
			ExitThread(0);
		if (j == 1) {
			EnterCriticalSection(&mute);
			cout << "T";
			Sleep(100);
			cout << "h";
			Sleep(100);
			cout << "r";
			Sleep(100);
			cout << "1 ";
			Sleep(100);
			if (n > 1)
				j++;
			LeaveCriticalSection(&mute);
		}
	}
	return 0;
}

DWORD WINAPI Thread_2(LPVOID t) {
	while(true){
		if (n == 1)
			ExitThread(0);
		if (j == 2) {
			EnterCriticalSection(&mute);
			cout << "T";
			Sleep(100);
			cout << "h";
			Sleep(100);
			cout << "r";
			Sleep(100);
			cout << "2 ";
			Sleep(100);
			if (n == 3) { j = 3; }
			else { j = 1; }
			LeaveCriticalSection(&mute);
		}
	}
	return 0;
}

DWORD WINAPI Thread_3(LPVOID t) {
	while (true) {
		if (n == 2)
			ExitThread(0);
		if (j == 3) {
			EnterCriticalSection(&mute);
			cout << "T";
			Sleep(100);
			cout << "h";
			Sleep(100);
			cout << "r";
			Sleep(100);
			cout << "3 ";
			Sleep(100);
			j = 1;
			LeaveCriticalSection(&mute);
		}
	}
	return 0;
}

int main()
{
	InitializeCriticalSection(&mute);
	char q = ' ';
	HANDLE thr1 = NULL, thr2 = NULL, thr3 = NULL;
	while (true) {
		rewind(stdin);
		q = _getch();
		if (q == '+' && n == 0) {
			thr1 = CreateThread(NULL, 0, Thread_1, NULL, 0, NULL);
			n++;
		}
		else {
			if (q == '+' && n == 1) {
				thr2 = CreateThread(NULL, 0, Thread_2, NULL, 0, NULL);
				n++;
			}
			else {
				if (q == '+' && n == 2) {
					thr3 = CreateThread(NULL, 0, Thread_3, NULL, 0, NULL);
					n++;
				}
			}
		}
		if (q == '-') {
			n--;
			Sleep(100);
		}
		if (q == 'q')
			break;
	}
	DeleteCriticalSection(&mute);
	return 0;
}