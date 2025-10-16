#include "searchengine.h"
using namespace std;

int main(int argc, char **argv) {
    if (argc != 5) {
        cout << "Wrong argument" << endl;
    }  else {
        cout << "correct args" << endl;
    }

    cout << "please wait" << endl;
    int linecounter = 0;
    int maxlength = -1;
    int k = atoi(argv[4]);

    if (read_sizes(&linecounter, &maxlength, argv[2]) == -1) {
        return -1;
    }
    
    return 0;
}