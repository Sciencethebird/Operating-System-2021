#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define RAND_SEED 69420
#define ARRAY_SIZE 1000000
#define MAX_NUM 10
#define COUNT_TARGET 6

int count_element(int a[], int start, int end, int target){
    int i, count = 0;
    for(i = start; i< end; i++){
        if(a[i] == target) count++;
    }
    return count;
}

int main(){
    // generating a random array
    int i, a[ARRAY_SIZE];
    srand(RAND_SEED);
    for(i = 0; i< ARRAY_SIZE; i++)
        a[i] = rand() % MAX_NUM;

    // count array element
    unsigned long diff;
    int num_count;
    timer_start();
    num_count = count_element(a, 0, ARRAY_SIZE, COUNT_TARGET);
    diff = timer_stop();

    printf("Integer %d occurs %d times in the array.\n", COUNT_TARGET, num_count);
    printf("Execution time %lu us\n", diff);
    return 0;
}