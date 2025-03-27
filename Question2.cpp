#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        fprintf(file, "Child process writing to file (PID=%d)\n", getpid());
        printf("Child process finished writing to file.\n");
    } else { 
        fprintf(file, "Parent process writing to file (PID=%d)\n", getpid());
        printf("Parent process finished writing to file.\n");
        waitpid(pid, NULL, 0); 
    }

    fclose(file);
    return 0;
}

