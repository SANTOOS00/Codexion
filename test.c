#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval start, end;

    // ⏱️ ابدأ
    gettimeofday(&start, NULL);

    // الكود اللي تبغي تقيسه
    long sum = 0;
    for (int i = 0; i < 100; i++)
        sum += i;

    // ⏱️ وقف
    gettimeofday(&end, NULL);

    // حساب الفرق بالـ ms
    double ms = (end.tv_sec  - start.tv_sec)  * 1000.0 +
                (end.tv_usec - start.tv_usec) / 1000.0;

    printf("sum  = %ld\n", sum);
    printf("time = %.3f ms\n", ms);

    return 0;
}