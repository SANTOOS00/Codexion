#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval start, end;

    gettimeofday(&start, NULL);

    long sum = 0;
    for (size_t i = 0; i < 1000000; i++)
        sum += i;

    gettimeofday(&end, NULL);

    size_t ms = (end.tv_sec  - start.tv_sec)  * 1000.0 +
                (end.tv_usec - start.tv_usec) / 1000.0;

    printf("sum  = %ld\n", sum);
    printf("time = %.3zu ms\n", ms);

    return 0;
}