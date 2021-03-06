# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include "timer.h"
# include "settings.h"

# define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef struct thread_arguments {
    int *a;
    int start;
    int end;
    int target;
} thargs_t;

thargs_t* init_args(int *a, int start, int end, int target){
    thargs_t* args = malloc(sizeof(thargs_t));
    args->a = a;
    args->start = start;
    args->end = end;
    args->target = target;
    return args;
}

void* count_element(void* thrgs){
    int i;
    thargs_t *arg = (thargs_t *) thrgs;
    int * count = malloc(sizeof(int));
    for(i = arg->start; i< arg->end; i++)
        if(arg->a[i] == arg->target) (*count)++;
    pthread_exit((void *) count);
}

int main(int argc, char **argv){
    
    /* parse argument */
    long long ARRAY_SIZE, MAX_NUM, NUM_OF_THREAD;
    int cmd_opt = 0, hide = 0, iter = 0;

    while(1) {
        cmd_opt = getopt(argc, argv, "s:m:n:i:h");
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
            case 'n':
                NUM_OF_THREAD = atoll(optarg);
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
    srand(RAND_SEED);
    int *a = malloc(ARRAY_SIZE * sizeof(int));
    for(int i = 0; i< ARRAY_SIZE; i++)
        a[i] = rand() % MAX_NUM;

    /* start counting */
    if(hide == 0) printf("start counting...\n");
   
    for(int n = 0; n < iter; n++){
        timer_start();
        /* create threads & execute */
        pthread_t t[NUM_OF_THREAD];
        int search_range = ARRAY_SIZE / NUM_OF_THREAD;
        int search_start = 0;

        for(int i = 0; i < NUM_OF_THREAD; i++){
            int upper_bound = MIN( (search_start + search_range), ARRAY_SIZE );
            thargs_t *args = init_args(a, search_start, upper_bound, COUNT_TARGET);
            pthread_create(&t[i], NULL, count_element, args);
            search_start += search_range;
        }

        /* collect results from threads */
        int total_count = 0;
        for(int i = 0; i < NUM_OF_THREAD; i++){
            void *ret;
            pthread_join(t[i], &ret); 
            int *count = (int *) ret;
            total_count += (*count);
        }

        /* timer stop */
        unsigned long diff = timer_stop();

        if(hide){
            printf("%lld, %d, %lu, ", NUM_OF_THREAD, total_count, diff);
        }else{
            printf("Integer %d occurs %d times in the array.\n", COUNT_TARGET, total_count);
            printf("Execution time %lu us\n", diff);
        }
    }
    printf("\n");
        
    free(a);
    return 0;
}