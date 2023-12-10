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
    int file1 = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_1", O_RDONLY);
    // int file2 = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_2", O_RDONLY);
    // int file3 = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_3", O_RDONLY);
    // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_3", O_RDONLY);
    // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_4", O_RDONLY);
    // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_5", O_RDONLY);
    // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_6", O_RDONLY);
    // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_7", O_RDONLY);
    // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_8", O_RDONLY);
    // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_9", O_RDONLY);
    // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_10", O_RDONLY);
    // int file1 = open("/home/madlab/CODE/PROJECT/42/tmp/test/hey/invalid_fd", O_RDONLY);
    int file2 = open("/home/madlab/CODE/PROJECT/42/tmp/test/hey/empty", O_RDONLY);
    int file3 = open("/home/madlab/CODE/PROJECT/42/tmp/test/hey/41_with_nl", O_RDONLY);
    // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/nohup.out", O_RDONLY);
    // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/hey/41_with_nl", O_RDONLY);
    // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/hey/nl", O_RDONLY);
    int fd;
    int all_file_null = 1;
    fd = file1;
    char *line = get_next_line(fd);
    while (all_file_null != 0)
    {
        if (line != NULL)
        {
            ft_printf("File %d :", fd);
            ft_printf("%s", line);
            all_file_null++;
            free(line);
        }
        if (fd == file1)
            fd = file2;
        else if (fd == file2)
            fd = file3;
        else
        {
            fd = file1;
            all_file_null = 0;
        }
        line = get_next_line(fd);
    }
    close(file1);
    close(file2);
    close(file3);
    ft_printf("\n\nBUFFER_SIZE = %d\n", BUFFER_SIZE);
    return (0);
}
