
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <semaphore.h>
# include <sys/wait.h>

void routine(sem_t *s, int x)
{
    sem_wait(s);
    printf("take fork %d\n",x);
    sem_wait(s);
    printf("take fork %d\n",x);
    printf("philo %d is eating\n", x);
    usleep(800000);
    sem_post(s);
    sem_post(s);
    printf("philo %d is sleeping\n",x);
    usleep(60000);
    printf("philo thinking\n");
}

int main()
{
    sem_t *s;
    char *se = "sr";
    int i;
    int x = 1;

    s = sem_open(se, O_CREAT,0644,6);
    while (x <= 6)
    {
        i = fork();
        if (i == 0)
        {
            routine(s,x);
			//monitor
            sem_close(s);
            exit(0);
        }
        x++;
    }
    while (wait(NULL) != -1);
    sem_unlink(se);
}