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
    // int fd = open("test/basic_8", O_RDONLY);
    // int fd = open("test/basic_9", O_RDONLY);
    int fd = open("test/basic_10", O_RDONLY);
    // int fd = open("test/nohup.out", O_RDONLY);
    char *line = get_next_line(fd);
    while (line)
    {
        ft_printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}