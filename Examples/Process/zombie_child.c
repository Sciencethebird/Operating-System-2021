// this exmaple is from https://wirelessr.gitbooks.io/working-life/content/wait_vs_waitpid.html
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

// Driver code
int main()
{
    int status, ret;
    switch (fork())
    {
        case -1:
            break;
        case 0:
            // execl("/util/AAA", "/util/AAA", "-s", "OOXX", NULL);
            printf("Child: %d\n", getpid());
            exit(1);
        default:
            // It's actually ok to have child exit before parent call wait()
            sleep(2);
            printf("Parent's waiting\n");
            wait(&status);
            if(WIFEXITED(status)) 
            {
                ret = WEXITSTATUS(status);
            } 
            else if(WIFSIGNALED(status))
            {
                ret = WTERMSIG(status);
            }
            printf("Parent, child's return %d\n", ret);
            break;
    }
    return 0;
}