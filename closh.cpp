#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    string program, mode;
    int count;

    cout << "closh> ";
    cin >> program;

    cout << "count> ";
    cin >> count;

    if (count < 1 || count > 9) {
        cerr << "Error: Count must be between 1 and 9." << endl;
        return 1;
    }

    cout << "[p]arallel or [s]equential> ";
    cin >> mode;

    for (int i = 0; i < count; ++i) {
        pid_t pid = fork();

        if (pid == 0) { 
            char *args[] = {const_cast<char*>(program.c_str()), NULL};
            execvp(args[0], args);
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else if (pid < 0) { 
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        // Sequential
        if (mode == "s" || mode == "S") {
            waitpid(pid, NULL, 0);
        }
    }

    // If parallel
    if (mode == "p" || mode == "P") {
        while (wait(NULL) > 0);
    }

    return 0;
}
