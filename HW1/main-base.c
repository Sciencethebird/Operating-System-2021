# include <stdio.h>
# include <stdlib.h>
# include "timer.h"
# include "settings.h"

int count_element(int* a, int start, int end, int target){
    int i, count = 0;
    for(i = start; i< end; i++)
        if(a[i] == target) count++;
    return count;
}

int main(){
    
    /* generating a random array */
    int i;
    srand(RAND_SEED);
    int *a = malloc(ARRAY_SIZE * sizeof(int));
    for(i = 0; i< ARRAY_SIZE; i++)
        a[i] = rand() % MAX_NUM;

    /* start counting */
    printf("start counting...\n");
    timer_start();

    int num_count = count_element(a, 0, ARRAY_SIZE, COUNT_TARGET);
    unsigned long  diff = timer_stop();

    printf("Integer %d occurs %d times in the array.\n", COUNT_TARGET, num_count);
    printf("Execution time %lu us\n", diff);

    free(a);
    return 0;
}