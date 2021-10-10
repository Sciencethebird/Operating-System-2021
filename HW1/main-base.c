# include <stdio.h>
# include <stdlib.h>
# include "timer.h"

# define RAND_SEED 69420
# define ARRAY_SIZE 1000000000
# define MAX_NUM 1000000
# define COUNT_TARGET 6

int count_element(int* a, int start, int end, int target){
    int i, count = 0;
    for(i = start; i< end; i++)
        if(a[i] == target) count++;
    return count;
}

int main(){
    
    int i;

    // generating a random array
    srand(RAND_SEED);
    int *a = malloc(ARRAY_SIZE * sizeof(int));
    for(i = 0; i< ARRAY_SIZE; i++)
        a[i] = rand() % MAX_NUM;

    unsigned long diff;
    int num_count;

    /* start counting */
    printf("start counting...\n");
    timer_start();

    num_count = count_element(a, 0, ARRAY_SIZE, COUNT_TARGET);
    diff = timer_stop();

    printf("Integer %d occurs %d times in the array.\n", COUNT_TARGET, num_count);
    printf("Execution time %lu us\n", diff);

    free(a);
    return 0;
}