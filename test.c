#include <stdio.h>
#include <sys/time.h>

int main()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("this time in microsecnds and this time in mail sconde %lld \n", (tv.tv_sec  * 1000000) + tv.tv_usec);

}