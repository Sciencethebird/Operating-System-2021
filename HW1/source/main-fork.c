# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "timer.h"
# include "settings.h"

# define MIN(a,b) ((a) < (b) ? (a) : (b))

int count_element(int* a, int start, int end, int target){
    int i, count = 0;
    for(i = start; i< end; i++)
        if(a[i] == target) count++;
    return count;
}

int main(int argc, char **argv){
    
    /* parse argument */
    long long ARRAY_SIZE, MAX_NUM, NUM_OF_CHILD;
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
                NUM_OF_CHILD = atoll(optarg);
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

    /* timer start */
    if(hide == 0) printf("start counting...\n");

    for(int n = 0; n < iter; n++){
        timer_start();

        /* variable for child process */
        pid_t pids[NUM_OF_CHILD];
        int search_range = ARRAY_SIZE / NUM_OF_CHILD;
        int search_start = 0;

        /* Start children. */
        for (int i = 0; i < NUM_OF_CHILD; ++i) {
            if ( (pids[i] = fork()) < 0 ) {
                perror("fork");
                abort();
            } else if ( pids[i] == 0 ) {
                int search_end = MIN( (search_start + search_range), ARRAY_SIZE );
                int count = count_element(a, search_start, search_end, COUNT_TARGET);
                if(count > 255) printf("Over 255 counts in one process!!\n");
                exit(count); // terminate child process otherwise it'
            }
            search_start += search_range;
        }

        /* Wait for children to exit. */
        int status, n = NUM_OF_CHILD, total_count = 0;
        pid_t pid;
        while (n > 0) {
          pid = wait(&status);
          if( WIFEXITED(status))  total_count += WEXITSTATUS(status);
          --n; 
        }

        /* timer stop */
        unsigned long diff = timer_stop();

        /* print result */
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
