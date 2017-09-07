// COPYRIGHT_BEGIN
// The MIT License (MIT)
//
// Copyright (c) 2017 Wizzer Works
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// COPURIGHT_END

// Include system header files.
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Todo: modify to capture stdout/stderr.
static int execProgram(const char **argv)
{
    pid_t pid;
    int   status, timeout /* unused ifdef WAIT_FOR_COMPLETION */;

    if (0 == (pid = fork())) {
        if (-1 == execve(argv[0], (char **)argv , NULL)) {
            perror("child process execve failed [%m]");
            return -1;
        }
    }

#ifdef WAIT_FOR_COMPLETION
    timeout = 1000;

    while (0 == waitpid(pid , &status , WNOHANG)) {
        if ( --timeout < 0 ) {
            perror("timeout");
            return -1;
        }
        sleep(1);
    }

    printf("%s WEXITSTATUS %d WIFEXITED %d [status %d]\n",
            argv[0], WEXITSTATUS(status), WIFEXITED(status), status);

    if (1 != WIFEXITED(status) || 0 != WEXITSTATUS(status)) {
        perror("%s failed, halt system");
        return -1;
    }

#endif
    return 0;
}

static char *fileExists(const char *dir, const char *file)
{
    // Build up the full path name of the file for the specified directory.
    char *dest = new char[strlen(dir) + strlen(file) + 2];
    memcpy(dest, dir, strlen(dir));
    memcpy(dest+strlen(dir), "/", 1);
    memcpy(dest+strlen(dir)+1, file, strlen(file));
    memcpy(dest+strlen(dir)+strlen(file)+1, "\0", 1);

    // stat dest to see if it exists.
    struct stat buf;
    if (stat(dest, &buf) == 0) {
        // File exists, returns allocated space containing full path.
        return dest;
    }

    delete dest;
    return NULL;
}

static char *findFile(const char *filename)
{
    char *fullpath = NULL;

    // Retrieve the PATH environment variable.
    char *dup = strdup(getenv("PATH"));

    // Initialize parsing.
    char *s = dup;
    char *p = NULL;
    do {
        // Parse for next entry.
        p = strchr(s, ':');
        if (p != NULL) {
            p[0] = 0;
        }

        // s is now pointing to a null-terminated entry in the PATH.
        printf("Path in $PATH: %s\n", s);
        // Search directory for path entry, s, and determine if filename is in the path.
        // If found, return the full path to the filename, "s/filename".
        char *fullpath = fileExists(s, filename);
        if (fullpath != NULL) {
            // Found file in parsed PATH entry.
            break;
        }

        // Increment past ':' to parse next entry.
        s = p + 1;
    } while (p != NULL);

    // Free up memory.
    free(dup);

    // Return full path to found file.
    return fullpath;
}

static bool runGltfValidator(const char *gltfFile)
{
    int status = -1;

    char *executable = findFile("gltf_validator");
    if (executable != NULL)
    {
        const char *argv[2];
        argv[0] = executable;
        argv[1] = gltfFile;
        status = execProgram(argv);

        // Error reporting is generated as a JSON file.

        // Clean up.
        delete executable;
    }

    return (status == 0);
}
