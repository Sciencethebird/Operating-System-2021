#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define RAND_SEED 69420
#define ARRAY_SIZE 10
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
    for(i = 0; i< ARRAY_SIZE; i++){ 
        a[i] = rand() % MAX_NUM;
        printf("%d ", a[i]);
    }
    printf("\n");

    // count array element
    int num_count;
    num_count = count_element(a, 0, ARRAY_SIZE, COUNT_TARGET);
    printf("Integer %d occurs %d times in the array.\n", COUNT_TARGET, num_count);
    return 0;
}