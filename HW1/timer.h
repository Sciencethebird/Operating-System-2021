#include <sys/time.h>
#include <unistd.h>

struct timeval start;
struct timeval end;

void timer_start(){
    gettimeofday(&start,NULL);
}
unsigned long timer_stop(){
    gettimeofday(&end,NULL);
    unsigned long diff;
    diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    return diff;
}
