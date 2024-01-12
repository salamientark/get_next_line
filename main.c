// #include "get_next_line_bonus.h"
// #include "get_next_line.h"
#include "testing.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int *make_fd_tab(int ac, char **av)
{
    int *fd_tab;
    int index;

    fd_tab = (int *)malloc(sizeof(int) * (ac - 1));
    if (!fd_tab)
        return (NULL);
    index = 0;
    while (index < (ac - 1))
    {
        fd_tab[index] = open(av[index + 1], O_RDONLY);
        index++;
    }
    return (fd_tab);
}

int    get_one_line_all_fd(int *fd_tab, int size)
{
    int     index;
    char    *line;
    int     end;

    index = 0;
    end = 0;
    while (index < size)
    {
        line = get_next_line(fd_tab[index]);
        if (line)
        {
            printf("%s|", line);
            free(line);
            end = 1;
        }
        index++;
    }
    return (end);
}

void    read_all_file_line_by_line(int *fd_tab, int size)
{
    while (get_one_line_all_fd(fd_tab, size))
        ;
}



void    read_file(int fd)
{
    char *line;

    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
}

void    read_all_file(int *fd_tab, int size)
{
    int index;

    index = 0;
    while (index < size)
    {
        read_file(fd_tab[index]);
        printf("-----------\n");
        index++;
    }
}

void    close_all(int *fd_tab, int size)
{
    int index;

    index = 0;
    while (index < size)
    {
        close(fd_tab[index]);
        index++;
    }
}

int main(int ac, char **av)
{
    int *fd_tab;
    int size;

    fd_tab = make_fd_tab(ac, av);
    if (!fd_tab)
    {
        printf("fd_tab : malloc error\n");
        return (0);
    }
    size = ac - 1;
    read_all_file_line_by_line(fd_tab, size);
    // read_all_file(fd_tab, size);
    close_all(fd_tab, size);
    free(fd_tab);
    return (0);
}
