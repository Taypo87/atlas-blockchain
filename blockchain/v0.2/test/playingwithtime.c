#include <time.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
    time_t now;

    now = time(NULL);

    printf("Current Unix timestamp: %ld\n", now);

    return 0;
}