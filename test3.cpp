#include <cstdio>
#include <string>
#include <vector>

#include <sys/wait.h>
#include <unistd.h>

int main() {
    using namespace std;

    vector<string> args;
    args.push_back("Hello");
    args.push_back("World");
    char **argv = new char*[args.size() + 2];
    argv[0] = "echo";
    argv[args.size() + 1] = NULL;
    for(unsigned int c=0; c<args.size(); c++)
        argv[c+1] = (char*)args[c].c_str();

    switch (fork()) {
    case -1:
        perror("fork");
        return 1;

    case 0:
        execvp(argv[0], argv);
        // execvp only returns on error
        perror("execvp");
        return 1;

    default:
        wait(0);
    }
    return 0;
}