#include "get_next_line_bonus.h"
// #include "get_next_line.h"
// #include "testing.h"
#include "../ft_printf/ft_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int file1 = open("../test/basic_1", O_RDONLY);
    int file2 = open("../test/basic_2", O_RDONLY);
    int file3 = open("../test/basic_3", O_RDONLY);
    // int fd = open("test/basic_4", O_RDONLY);
    // int fd = open("test/basic_5", O_RDONLY);
    // int fd = open("test/basic_6", O_RDONLY);
    // int fd = open("test/basic_7", O_RDONLY);
    // int fd = open("test/basic_8", O_RDONLY);
    // int fd = open("test/basic_9", O_RDONLY);
    // int fd = open("test/basic_10", O_RDONLY);
    // int fd = open("test/nohup.out", O_RDONLY);
    // int fd = open("test/hey/41_with_nl", O_RDONLY);
    // int fd = open("test/hey/nl", O_RDONLY);
    int fd;
    fd = file1;
    char *line = get_next_line(fd);
    ft_printf("File %d :", fd);
    while (line)
    {
        ft_printf("%s", line);
        free(line);
        if (fd == file1)
            fd = file2;
        else if (fd == file2)
            fd = file3;
        else if (fd == file3)
            fd = file1;
        ft_printf("File %d :", fd);
        line = get_next_line(fd);
    }
    close(fd);
    ft_printf("\n\nBUFF_SIZE = %d\n", BUFF_SIZE);
    return (0);
}
