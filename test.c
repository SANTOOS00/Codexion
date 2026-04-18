#include <stdio.h>
#include <sys/time.h>
long ft_gettime_ms()
{
        struct timeval new;
        gettimeofday(&new, NULL);
        return (new.tv_sec * 1000) + (new.tv_usec / 1000);
}

unsigned long ft_gettime(unsigned long time_create_coder)
{
        struct timeval new;
        gettimeofday(&new, NULL);
        return (new.tv_sec * 1000) + (new.tv_usec / 1000) - time_create_coder;
}


}
