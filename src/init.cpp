#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <linux/limits.h>
#include "init.h"
using namespace std;

int initSystem(const char *prog) {
    ofstream CLR("/proc/sys/fs/binfmt_misc/CLR");
    if ( CLR ) {
        CLR << "-1";
        CLR.close();
    }
    ofstream reg("/proc/sys/fs/binfmt_misc/register");
    if ( reg ) {
        char buffer[PATH_MAX];
        reg << ":CLR:M::\\x4d\\x5a::" << realpath(prog, buffer) << ":";
        reg.close();
    } else {
        return EACCES;
    }
    return 0;
}
