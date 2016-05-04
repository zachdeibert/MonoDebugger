#include <iostream>
#include "help.h"
using namespace std;

void showHelp(const char *prog) {
    cerr << "Usage: " << prog << " [--init] [program [program-options]]" << endl
         << endl
         << "Options:" << endl
         << "    --init     Initializes binfmt_misc to automatically load " << prog << " instead of mono." << endl;
}
