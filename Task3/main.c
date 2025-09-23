#include <stdio.h>      // printf, fprintf, perror, FILE operations
#include <stdlib.h>     // exit, EXIT_FAILURE, EXIT_SUCCESS
#include <unistd.h>     // fork, execvp, pipe, dup2, close
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait, waitpid, WEXITSTATUS macros
#include <fcntl.h>      // open, O_WRONLY, O_CREAT, O_TRUNC
#include <string.h>     // strerror (optional, for printing errors)
#include <errno.h>      // errno


int main(int argc, char *argv[]){
    if (argc != 5) {
        fprintf(stderr, "Usage: %s prog1 prog2 prog3 output_file\n", argv[0]);
        return -1;
    }

    char *prog1 = argv[1];
    char *prog2 = argv[2];
    char *prog3 = argv[3];
    char *outfile = argv[4];

    pid_t cpid;
    cpid = fork();

    if (cpid < 0) {
        perror("fork");
        exit(1);
    }

    if(cpid == 0){
        char * args[] = {prog1, NULL};
        execvp(prog1,args);

        perror("execvp prog1");
        exit(1);

    }
    int status;
    waitpid(cpid, &status, 0);

    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        // prog1 failed, stop here
        printf("prog1 failed, exiting.\n");
        exit(1);
    }

    int pipefd[2];
    
    if (pipe(pipefd) == -1) { perror("pipe"); exit(1); }

    cpid = fork();
    if (cpid < 0) {
        perror("fork");
        exit(1);
    }
    if(cpid == 0){
        close(pipefd[0]);
        dup2(pipefd[1],STDOUT_FILENO);
        char * args[] = {prog2, NULL};
        execvp(prog2,args);

        perror("execvp prog2");
        exit(1);

    }

    cpid = fork();
    if (cpid < 0) {
        perror("fork");
        exit(1);
    }
    if(cpid == 0){
        close(pipefd[1]);
        dup2(pipefd[0],STDIN_FILENO);
        
        int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) { perror("open outfile"); exit(1); }
        dup2(fd, STDOUT_FILENO);
        close(fd);

        char * args[] = {prog3, NULL};
        execvp(prog3,args);

        perror("execvp prog3");
        exit(1);

    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);

}