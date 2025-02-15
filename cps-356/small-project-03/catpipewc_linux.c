#ifndef FILEPIPE_C
#define FILEPIPE_C

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// EXAMPLE CODE FROM THE BOOK ON HOW TO PIPE (it actually works, try it! Just uncomment the following line):
// #define TEST_ORIG

#ifdef TEST_ORIG

int main()
{
    int p[2];
    char *argv[2];
    argv[0] = "wc";
    argv[1] = 0;
    pipe(p);
    if (fork() == 0)
    {
        close(0);
        dup(p[0]);
        close(p[0]);
        close(p[1]);
        execvp("/bin/wc", argv);
    }
    else
    {
        close(p[0]);
        write(p[1], "hello world\n", 12);
        close(p[1]);
    }

    return 0;
}

#else

char buf[512];

int main(int argc, char **argv)
{
    // We should be reading and word-counting at least one file...
    if (argc < 2)
    {
        return -1;
    }

    // Generate file descriptions for the read and write ends of the pipe
    int pipe_fds[2];
    pipe(pipe_fds);

    // fork() will create a child process...
    // This first path is the execution of the child process, and the else is for the parent
    if (fork() == 0)
    {
        // Close the stdin stream and replace it with the read end of the pipe.
        // After this, fd 0 will be the read end of the pipe.
        close(0);
        dup(pipe_fds[0]);

        // Close both of the pipe's file descriptors. Note that this does not close fd 0,
        // only the ORIGINAL descriptors given to the pipe.
        close(pipe_fds[0]);
        close(pipe_fds[1]);

        // Execvp() is the Linux function for calling another process.
        // It replaces the current process with the called process.
        char *args[] = {"wc", 0};
        execvp("/bin/wc", args);
    }
    else
    {
        // Close the read channel...we won't need it. This is the first leg of the pipe.
        close(pipe_fds[0]);

        // Taken from the "cat" code in xv6, modified for this program...
        int fd, n;
        for (int i = 1; i < argc; ++i)
        {
            if ((fd = open(argv[i], 0)) < 0)
            {
                printf("cat: cannot open %s\n", argv[i]);
                return -1;
            }

            while ((n = read(fd, buf, sizeof(buf))) > 0)
            {
                // Instead of writing to stdout, we write to the write fd for the pipe.
                if (write(pipe_fds[1], buf, n) != n)
                {
                    printf("cat: write error\n");
                    return -1;
                }
            }
            if (n < 0)
            {
                printf("cat: read error\n");
                return -1;
            }
            close(fd);
        }

        // Close the write channel now that we've finished reading all the files.
        close(pipe_fds[1]);
    }
    return 0;
}

#endif

#endif
