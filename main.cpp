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
#include <time.h>
using namespace std;

int counter;

void func(int sig)

{   int a;
    counter++;
    int status;
    int proc = fork();
    clock_t start = clock();
    if (proc == 0) {
        cout << endl << "__________Дочерний процесс__________" << endl << "pid = " << getpid() << endl;
        time_t  timev;
        time(&timev);
        cout << "Запуск дочернего процесса " << ctime(&timev) << endl;
        for (int i = 0; i < 10000000; i++)
        {a = 5+4*500000;}


        exit(0);
    } else{


        waitpid(proc, &status, WNOHANG);

        clock_t stop = clock();
        cout << "Время работы дочернего процесса с pid " << proc << " " <<(stop- start) << " такта" << endl; //Получаем время работы дочернего процесса в секундах

        cout << "Время работы программы " << clock() << " тактов" << endl << "_____________________________________________________" << endl;
        return;
    }

}

int main(int argc, char * argv[]) {
    counter = 0;

    struct itimerval  A,B;
    struct sigaction act;
    /* установка реакции на сигнал SIGALRM*/
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGALRM,&act,0);

    /* установка периода перезапуска программы*/
    A.it_interval.tv_sec=atoi(argv[1]);
    A.it_interval.tv_usec=100000; // период перезапуска 100 мс
    A.it_value.tv_usec=0;
    A.it_value.tv_sec=2; // первый запуск через 2 сек
    setitimer(ITIMER_REAL, &A,  &B);
    for (;;)
    {
        if (counter >= atoi(argv[2]))
            return 1;

    } /* бесконечный цикл ожидания  сигнала SIGALRM*/





    return 0;
}