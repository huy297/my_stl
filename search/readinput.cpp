#include "Readinput.h"
using namespace std;

int read_size(int *linecounter, int *maxlength, char* docfile) {
    FILE *file = fopen(docfile, "r");

    if (file == NULL) {
        cout << "Error opening file" << endl;
        return -1;
    }

    
}