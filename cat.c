#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

extern int errno;

void print_File(char fileName[1000])
{
    int fd = open(fileName, O_RDONLY);
    if (fd < 0)
    {
        perror("File Not Present Error");
        return;
    }
    char ch;
    int sz;
    while ((sz = read(fd, &ch, 1)))
    {
        if (sz < 0)
        {
            perror("read");
            return;
        }
        size_t w = write(STDIN_FILENO, &ch, 1);
        if (w < 0)
        {
            if (errno != EINTR)
            {
                perror("write");
                return;
            }
        }
    }
    if (close(fd) < 0)
    {
        perror("close");
        return;
    }
    return;
}

void print_FileDollar(char fileName[1000])
{
    int fd = open(fileName, O_RDONLY);
    if (fd < 0)
    {
        perror("File Not Present Error");
        return;
    }
    char ch;
    int sz;
    while ((sz = read(fd, &ch, 1)))
    {
        if (sz < 0)
        {
            perror("read");
            return;
        }
        if (ch == '\n')
        {
            char c = '$';
            size_t w = write(STDIN_FILENO, &c, 1);
            if (w < 0)
            {
                if (errno != EINTR)
                {
                    perror("write");
                    return;
                }
            }
        }
        write(STDIN_FILENO, &ch, 1);
    }
    if (close(fd) < 0)
    {
        perror("close");
        return;
    }
    return;
}

void print_FileTab(char fileName[1000])
{
    int fd = open(fileName, O_RDONLY);
    if (fd < 0)
    {
        perror("File Not Present Error");
        return;
    }
    char ch;
    int sz;
    while ((sz = read(fd, &ch, 1)))
    {
        if (sz < 0)
        {
            perror("read");
            return;
        }
        if (ch == 9)
        {
            char c = '^';
            size_t w;
            w = write(STDIN_FILENO, &c, 1);
            if (w < 0)
            {
                if (errno != EINTR)
                {
                    perror("write");
                    return;
                }
            }
            c = 'I';
            w = write(STDIN_FILENO, &c, 1);
            if (w < 0)
            {
                if (errno != EINTR)
                {
                    perror("write");
                    return;
                }
            }
        }
        else
        {
            size_t w = write(STDIN_FILENO, &ch, 1);
            if (w < 0)
            {
                if (errno != EINTR)
                {
                    perror("write");
                    return;
                }
            }
        }
    }
    if (close(fd) < 0)
    {
        perror("close");
        return;
    }
}

int main(int argc, char *argv[])
{
    char commandName[10] = "";
    char flag[10] = "";
    char fileName[1000] = "";
    char *token = strtok(argv[1], " ");
    strcpy(commandName, token);
    token = strtok(NULL, " ");
    if (token[0] == '-')
    {
        strcpy(flag, token);
        token = strtok(NULL, " ");
    }
    while (token != NULL)
    {
        strcpy(fileName, token);
        if (strcmp(flag, "") == 0)
        {
            print_File(fileName);
        }
        else if (flag[1] == 'E')
        {
            print_FileDollar(fileName);
        }
        else if (flag[1] == 'T')
        {
            print_FileTab(fileName);
        }
        else
        {
            printf("Invalid Input -- %s\n", flag);
            return 1;
        }
        token = strtok(NULL, " ");
    }
    return 0;
}