# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "timer.h"
# include "settings.h"

# define NUM_OF_CHILD 10
# define MIN(a,b) ((a) < (b) ? (a) : (b))

int count_element(int* a, int start, int end, int target){
    int i, count = 0;
    for(i = start; i< end; i++)
        if(a[i] == target) count++;
    return count;
}

int main(){
    
    /* generating a random array */
    srand(RAND_SEED);
    int *a = malloc(ARRAY_SIZE * sizeof(int));
    for(int i = 0; i< ARRAY_SIZE; i++)
        a[i] = rand() % MAX_NUM;

    /* timer start */
    printf("start counting...\n");
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
      // status = status >> 8; // exit info stored in upper 8 bit of status
      // total_count += status;
      --n; 
    }

    /* timer stop */
    unsigned long diff = timer_stop();

    /* print result */
    printf("Integer %d occurs %d times in the array.\n", COUNT_TARGET, total_count);
    printf("Execution time %lu us\n\n", diff);

    free(a);
    return 0;
}
