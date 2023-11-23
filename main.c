#include "get_next_line.h"
#include "testing.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{
    // int fd = open("test/basic_1", O_RDONLY);
    int fd = open("test/basic_2", O_RDONLY);
    char *line = get_next_line(fd);
    ft_printf("line 1: %s", line);
    line = get_next_line(fd);
    ft_printf("line 2: %s", line);

    close(fd);
    return (0);
}