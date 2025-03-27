#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        printf("hello\n");
        exit(0); 
    } else {
        usleep(100); // Delay
        printf("goodbye\n");
    }

    return 0;
}
