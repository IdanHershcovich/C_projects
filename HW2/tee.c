#include "csapp.h"

int main(int argc, char **argv)
{
    int n;
    int fd;
    int c;
    char buf[MAXLINE];
    rio_t rio;

    if (argc == 2)
    {
        fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

        print("file %s was created and truncated successfully! \n", argv[1]);
    }

    else if ((c = getopt(argc, argv, "a:")) != -1)
    {
        fd = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    Rio_readinitb(&rio, STDIN_FILENO);
    while ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        rio_writen(STDOUT_FILENO, buf, n);
        rio_writen(fd, buf, n);
    }

    close(fd);
    exit(0);
}