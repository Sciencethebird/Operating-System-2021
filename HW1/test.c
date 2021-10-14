#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>

#define ARY_SIZE 1000000000

int main(void)
{
   srand(69420);
   static int InputData[ARY_SIZE];
   for(int i=0;i<ARY_SIZE;i++)
        InputData[i]=rand()%1000000;
    
    int inQRY;
    printf("Please key the inquiry number(0~99): ");
    scanf("%d", &inQRY);

    struct timeval START, END;
    struct timeval START1, END1;
    struct timeval START2, END2;
    struct timezone tz;
    gettimeofday(&START, &tz);

    int NUM_times =0;
    for(int i=0;i<ARY_SIZE;i++){
        if(InputData[i]==inQRY){
            NUM_times++;
        }
    }

    printf("Integer %d occurs %d times in the array", inQRY, NUM_times);

    gettimeofday(&END, &tz);
    printf("\nSTART  Time: %ld \n", (long)(START.tv_usec));
    printf("END  Time: %ld ", (long)(END.tv_usec));
    
    printf("\nCost Time: %ld usec\n", (long)(END.tv_usec+END.tv_sec*1000000-START.tv_usec-START.tv_sec*1000000));


    /*mult-process*/
    //printf("Parent(pid:%d)\n",(int)getpid());
    gettimeofday(&START1, &tz);
    int rc = fork();
    int child_status,child_status2;
    NUM_times =0;
    if(rc<0){
        //fork fail
        perror("fork error");
        exit(EXIT_FAILURE);
    }else if(rc==0){
        //child1
        //printf("Child(pid:%d)\n",(int)getpid());
        int rc2 =fork();
        int NUM_times2 =0;
        if(rc2<0){
            //fork fail
            perror("fork error");
            exit(EXIT_FAILURE);
        }else if(rc2==0){
            //child2
            //printf("Child2(pid:%d)\n",(int)getpid());
            int NUM_times =0;
            for(int i=0;i<ARY_SIZE/2;i++){
                if(InputData[i]==inQRY){
                NUM_times++;
                }
            }
            exit(NUM_times);
        }else{
            //child1 / Parent2
            
            for(int i=ARY_SIZE/2;i<ARY_SIZE;i++){
                if(InputData[i]==inQRY){
                NUM_times2++;
                }
            }
            //wait for child2
            int rc2_wait_pid = wait(&child_status2);//wait for child finish
        }
        exit(NUM_times2+WEXITSTATUS(child_status2));
    }else{
        //parent
        int rc_wait_pid = wait(&child_status);//wait for child finish
        //printf("Parent(pid:%d)\n",(int)getpid());
        printf("Integer %d occurs %d times in the array",inQRY,WEXITSTATUS(child_status));
        gettimeofday(&END1, &tz);
        printf("\nSTART  Time: %ld \n", (long)(START1.tv_usec));
        printf("END  Time: %ld ", (long)(END1.tv_usec));
        printf("\nCost Time: %ld usec\n", (long)(END1.tv_usec+END1.tv_sec*1000000-START1.tv_usec-START1.tv_sec*1000000));
    }


    int num_process=5;
    int num_p =num_process;
    int i;
    int status[num_process];
    int size_seg= ARY_SIZE/num_process;
    gettimeofday(&START2, &tz);
    for(i=0; i<num_process; i++){
        pid_t fpid =fork();
        if(fpid ==0){
            int NUM_times =0;
            int j;
            for(j=i*size_seg ;j<size_seg*(i+1);j++){
                if(InputData[j]==inQRY){
                    NUM_times++;
                }
            }
            //printf("son %d\n",i);
            exit(NUM_times);
        }
    }

    int stat;
    pid_t pid;
    int total_num_times =0;
    while(num_p>0){
        pid =wait(&stat);
        //printf("pide: %ld, re: %d\n",(long)pid, WEXITSTATUS(stat));
        total_num_times= total_num_times+WEXITSTATUS(stat);
        --num_p;
    }
    printf("Integer %d occurs %d times in the array",inQRY,total_num_times);
    gettimeofday(&END2, &tz);
    printf("\nSTART  Time: %ld \n", (long)(START2.tv_usec));
    printf("END  Time: %ld ", (long)(END2.tv_usec));
    printf("\nCost Time: %ld usec\n", (long)(END2.tv_usec+END2.tv_sec*1000000-START2.tv_usec-START2.tv_sec*1000000));











    return 0;
}