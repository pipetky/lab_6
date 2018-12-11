#include <sys/times.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
using namespace std;


void func(int sig)
{   int a;
    int status;
    int proc =fork();
    if (proc == 0) {
        cout << "__________Дочерний процесс__________" << endl << "pid = " << getpid() << endl;
        for (int i = 0; i < 100; i++)
        {a = 5+4;}
        exit(0);
    } else{
        struct tms pb1, pb2;
        times(&pb2);
        waitpid(proc, &status, WNOHANG);

        times(&pb1);
        cout << pb1.tms_stime - pb2.tms_stime << endl;
        cout << clock() << endl;
        return;
    }

}

int main() {

    struct itimerval  A,B;
    struct sigaction act;
    /* установка реакции на сигнал SIGALRM*/
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGALRM,&act,0);
    /* установка периода перезапуска программы*/
    A.it_interval.tv_sec=1;
    A.it_interval.tv_usec=100000; // период перезапуска 100 мс
    A.it_value.tv_usec=0;
    A.it_value.tv_sec=2; // первый запуск через 2 сек
    setitimer(ITIMER_REAL, &A,  &B);
    for (;;) pause(); /* бесконечный цикл ожидания  сигнала SIGALRM*/





    return 0;
}