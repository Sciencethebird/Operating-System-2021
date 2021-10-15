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

int main(int argc, char **argv){
    
    /* parse argument */
    long long ARRAY_SIZE, MAX_NUM;
    int cmd_opt = 0, hide = 0, iter;

    while(1) {
        cmd_opt = getopt(argc, argv, "s:m:i:h");
        /* no more argument to parse */
        if (cmd_opt == -1) break;
        switch (cmd_opt) {
            case 's':
                ARRAY_SIZE = atoll(optarg);
                break;
            case 'm':
                MAX_NUM = atoll(optarg);
                break;
            case 'h':
                hide = 1;
                break;
            case 'i':
                iter = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Not supported option\n");
                break;
        }
    }

    /* generating a random array */
    int i;
    srand(RAND_SEED);
    int *a = malloc(ARRAY_SIZE * sizeof(int));
    for(i = 0; i< ARRAY_SIZE; i++)
        a[i] = rand() % MAX_NUM;

    /* start counting */
    if(hide == 0) printf("start counting...\n");
    for(int n = 0; n<iter; n++){
        timer_start();
        int total_count = count_element(a, 0, ARRAY_SIZE, COUNT_TARGET);
        unsigned long  diff = timer_stop();
        if(hide){
            printf("%lld, %d, %lu, ", ARRAY_SIZE, total_count, diff);
        }else{
            printf("Integer %d occurs %d times in the array.\n", COUNT_TARGET, total_count);
            printf("Execution time %lu us\n", diff);
        }
    }
    printf("\n");
    free(a);
    return 0;
}