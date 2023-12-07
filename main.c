#include "get_next_line.h"
#include "./ft_printf/ft_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

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
    // int fd = open("test/basic_10", O_RDONLY);
    // int fd = open("test/nohup.out", O_RDONLY);
    int fd = open("test/hey/41_with_nl", O_RDONLY);
    // int fd = open("test/hey/41_no_nl", O_RDONLY);
    // int fd = open("test/hey/nl", O_RDONLY);
    // int fd = open("test/hey/empty", O_RDONLY);
    char *line = get_next_line(fd);
    while (line)
    {
        ft_printf("%5d: %s", strlen(line), line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    ft_printf("\n\nBUFFER_SIZE = %d\n", BUFFER_SIZE);
    return (0);
}
