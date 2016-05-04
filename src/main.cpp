#include <cerrno>
#include <cstring>
#include <unistd.h>
#include "help.h"
#include "init.h"
#include "log.h"

int main(int argc, const char *argv[]) {
    bool init = false;
    bool help = true;
    const char *executable = NULL;
    const char **pargv;
    int pargc = 0;
    for ( int i = 1; i < argc; ++i ) {
        if ( strcmp(argv[i], "--init") == 0 ) {
            init = true;
            help = false;
        } else if ( strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0 ) {
            help = true;
            break;
        } else {
            if ( strcmp(argv[i], "--") == 0 ) {
                ++i;
            }
            executable = argv[i];
            pargv = argv + ++i;
            pargc = argc - i;
            help = false;
            break;
        }
    }
    if ( help ) {
        showHelp(argv[0]);
        return EINVAL;
    }
    if ( init ) {
        int res = initSystem(argv[0]);
        if ( res != 0 ) {
            return res;
        }
    }
    if ( executable != NULL ) {
        char *nargv[pargc + 4];
        nargv[0] = const_cast<char *>("/usr/bin/mono");
        nargv[1] = const_cast<char *>("--debug");
        nargv[2] = const_cast<char *>(executable);
        LOG("/usr/bin/mono --debug ")
        LOG(executable)
        for ( int i = 0; i < pargc; ++i ) {
            LOG(" ")
            LOG(pargv[i])
            nargv[i + 3] = const_cast<char *>(pargv[i]);
        }
        nargv[pargc + 3] = 0;
        LOG_LINE
        execv("/usr/bin/mono", nargv);
        return errno;
    }
    return 0;
}
