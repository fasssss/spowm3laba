#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <semaphore.h>
#include <string>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main()
{
    system("clear");
    bool flag = true;
    int fields[2] = {};
    if (pipe(fields))
        exit(-2);
    string str;
    sem_t *semaphore = sem_open("/Client-ServerSem", O_CREAT, O_RDWR | S_IRWXU, NULL);
    if (semaphore == SEM_FAILED)
    {
        cout << "Error!" << endl;
        exit(-3);
    }

    pid_t pid = fork();
    switch (pid)
    {
        case 0:{
            char strMas[BUFSIZ] = {};
            sem_wait(semaphore);
            read(fields[0], strMas, BUFSIZ);
            cout << endl << "I caught the message:\t" << strMas << endl << endl;
            sem_post(semaphore);
            usleep(1500000);
            sem_close(semaphore);
            exit(0);
        }
        default:
        {

            cout << "Enter string :" << endl;
            getline(cin, str);
            write(fields[1], str.c_str(), str.size()); 
            cout << "Waiting for client application..." << endl;
            sem_post(semaphore);
            usleep(1000000);
            sem_wait(semaphore);
            sem_unlink("/Client-ServerSem");
        }
    }
    wait(NULL);
    return 0;
}
