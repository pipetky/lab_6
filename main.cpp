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
struct timeval start_time;
struct timezone tz;



void func(int sig)

{   int a;
    counter++;
    struct timeval *start, stop;
    time_t  timev;
    int status;
    int proc = fork();

    if (proc == 0) {
        gettimeofday(start, &tz);
        cout << endl << "__________Дочерний процесс__________" << endl << "pid = " << getpid() << endl;


        time(&timev);
        cout << "Запуск дочернего процесса " << ctime(&timev) << endl;
        for (int i = 0; i < 10000000; i++)
        {a = 5+4*500000;}


        exit(0);
    } else{

        if (proc > 0) {
            waitpid(proc, &status, NULL);

            gettimeofday(&stop, &tz);
            cout << "Время работы дочернего процесса с pid " << proc << " " << (stop.tv_sec - start.tv_sec) << " сек"
                 << endl; //Получаем время работы дочернего процесса в секундах

            cout << "Время работы программы " << (stop.tv_sec - start_time.tv_sec) << " сек" << endl
                 << "_____________________________________________________" << endl;
        }
        return;
    }

}

int main(int argc, char * argv[]) {
    counter = 0;
    tz.tz_minuteswest = 0;
    tz.tz_dsttime = 0;



    gettimeofday(&start_time, &tz);


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