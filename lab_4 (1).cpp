#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>

using namespace std;
pthread_mutex_t mut;
int n = 0, j = 1;
void* thread1(void* arg){
    while(true){
        if(n == 0){
            pthread_exit(NULL);
        }
        if(j == 1){
            pthread_mutex_lock(&mut);
            cout << "T";
            //usleep(10000);
            cout << "H";
            //usleep(10000);
            cout << "1 ";
            //usleep(10000);
            if(n > 1){
                j++;
            }

        pthread_mutex_unlock(&mut);
        }
    }
}
void* thread2(void* arg){
    while(true){
        if(n == 1){
            pthread_exit(NULL);
        }
        if(j == 2){
            
            pthread_mutex_lock(&mut);
            cout << "T";
            //usleep(100000);
            cout << "H";
            //usleep(100000);
            cout << "2 ";
            //usleep(100000);
            if(n == 3){j = 3;}
            else{j = 1;}
            
            pthread_mutex_unlock(&mut);
        }
    }
}
void* thread3(void* arg){
    while(true){
        if(n == 2){
            pthread_exit(NULL);
        }
        if(j == 3){
            pthread_mutex_lock(&mut);
            cout << "T";
            //usleep(100000);
            cout << "H";
            //usleep(100000);
            cout << "3 ";
            //usleep(100000);
            j = 1;
            
            pthread_mutex_unlock(&mut);
        }
    }
}

int main()
{
    pthread_mutex_init(&mut, NULL);
    char q = ' ';
    pthread_t pthr1, pthr2, pthr3;
    while(true){
        cin >> q;
        if(q == '+' && n == 0){
            pthread_create(&pthr1, NULL, thread1, NULL);
            n++;
        }else{
            if(q == '+' && n == 1){
                pthread_create(&pthr2, NULL, thread2, NULL);
                n++;
            }else{
                if(q == '+' && n == 2){
                    pthread_create(&pthr3, NULL, thread3, NULL);
                    n++;
                }
            }
        }
        if(q == '-'){
            n--;
        }
        if(q == 'q'){
            break;
        }
    }
    pthread_mutex_destroy(&mut);
    return 0;
}