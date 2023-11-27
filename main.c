#include "get_next_line.h"
#include "testing.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{
    // int fd = open("test/basic_1", O_RDONLY);
    // int fd = open("test/basic_2", O_RDONLY);
    // int fd = open("test/basic_3", O_RDONLY);
    // int fd = open("test/basic_4", O_RDONLY);
    // int fd = open("test/basic_5", O_RDONLY);
    // int fd = open("test/basic_6", O_RDONLY);
    // int fd = open("test/basic_7", O_RDONLY);
    int fd = open("test/basic_8", O_RDONLY);
    char *line = get_next_line(fd);
    ft_printf("line 1: %s", line);
    line = get_next_line(fd);
    ft_printf("line 2: %s", line);
    line = get_next_line(fd);
    ft_printf("line 3: %s", line);
    line = get_next_line(fd);
    ft_printf("line 4: %s", line);
    close(fd);
    free(line);
    return (0);
}