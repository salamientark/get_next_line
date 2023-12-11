#include "get_next_line_bonus.h"
// #include "get_next_line.h"
// #include "testing.h"
#include "../ft_printf/ft_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void    read_all_file_to_the_end(int *tab, int size)
{
    int     index;
    int     end_of_all_file;
    int     fd;
    char    *gnl_result;

    index = 0;
    end_of_all_file = 1;
    while (!(end_of_all_file == 0 && index == size))
    {
        fd = tab[index];
        gnl_result = get_next_line(fd);
        if (!gnl_result)
        {
            ft_printf("FILE %d: %s", fd, gnl_result);
        }
        else
        {
            ft_printf("FILE %d: %s", fd, gnl_result);
            end_of_all_file = 1;
            free(gnl_result);
        }
        index++;
        if (index == size && end_of_all_file == 1)
        {
            index = 0;
            end_of_all_file = 0;
        }
    }
    // if (gnl_result)
        // free(gnl_result);
}

void    add_file(const char *filename, int *tab, int *size)
{
    tab[*size] = open(filename, O_RDONLY);
    *size = *size + 1;
}

void    close_all(int **tab, int size)
{
    int index = 0;

    while (index < size)
    {
        if (*tab[index] != -1)
            close(*tab[index]);
        index++;
    }
}

void    print_tab(int *tab, int size)
{
    int index = 0;

    ft_printf("-- PRINT_TAB --\n");
    ft_printf("size: %d\n", size);
    while (index < size)
    {
        printf("tab[%2d]: %d\n", index, tab[index]);
        index++;
    }
}

int main()
{
    // int *allfile = (int *)malloc(sizeof(int) * 3);
    // if (!allfile)
    //     return (0);
    int all_file[20];
    int size = 0;

    add_file("/home/madlab/CODE/PROJECT/42/tmp/test/hey/invalid_fd", all_file, &size);
    add_file("/home/madlab/CODE/PROJECT/42/tmp/test/hey/empty", all_file, &size);
    add_file("/home/madlab/CODE/PROJECT/42/tmp/test/hey/nl", all_file, &size);
    add_file("/home/madlab/CODE/PROJECT/42/tmp/test/hey/41_with_nl", all_file, &size);
    add_file("/home/madlab/CODE/PROJECT/42/tmp/test/hey/41_no_nl", all_file, &size);
    add_file("/home/madlab/CODE/PROJECT/42/tmp/test/hey/41_with_nl", all_file, &size);
    add_file("/home/madlab/CODE/PROJECT/42/tmp/test/hey/42_no_nl", all_file, &size);
    add_file("/home/madlab/CODE/PROJECT/42/tmp/test/hey/42_with_nl", all_file, &size);
    add_file("/home/madlab/CODE/PROJECT/42/tmp/test/hey/43_no_nl", all_file, &size);
    add_file("/home/madlab/CODE/PROJECT/42/tmp/test/hey/43_with_nl", all_file, &size);
    add_file("/home/madlab/CODE/PROJECT/42/tmp/test/hey/43_with_nl", all_file, &size);
    add_file("/home/madlab/CODE/PROJECT/42/tmp/test/hey/alternate_line_nl_no_nl", all_file, &size);

    // print_tab(all_file, size);
    read_all_file_to_the_end(all_file, size);


    // close_all((int **)&all_file, size);
    // print_tab(all_file, size);


    // int file1 = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_1", O_RDONLY);
    // // int file2 = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_2", O_RDONLY);
    // // int file3 = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_3", O_RDONLY);
    // // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_3", O_RDONLY);
    // // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_4", O_RDONLY);
    // // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_5", O_RDONLY);
    // // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_6", O_RDONLY);
    // // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_7", O_RDONLY);
    // // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_8", O_RDONLY);
    // // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_9", O_RDONLY);
    // // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/basic_10", O_RDONLY);
    // // int file1 = open("/home/madlab/CODE/PROJECT/42/tmp/test/hey/invalid_fd", O_RDONLY);
    // int file2 = open("/home/madlab/CODE/PROJECT/42/tmp/test/hey/empty", O_RDONLY);
    // int file3 = open("/home/madlab/CODE/PROJECT/42/tmp/test/hey/41_with_nl", O_RDONLY);
    // // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/nohup.out", O_RDONLY);
    // // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/hey/41_with_nl", O_RDONLY);
    // // int fd = open("/home/madlab/CODE/PROJECT/42/tmp/test/hey/nl", O_RDONLY);
    // int fd;
    // int all_file_null = 1;
    // fd = file1;
    // char *line = get_next_line(fd);
    // while (all_file_null != 0)
    // {
    //     if (line != NULL)
    //     {
    //         ft_printf("File %d :", fd);
    //         ft_printf("%s", line);
    //         all_file_null++;
    //         free(line);
    //     }
    //     if (fd == file1)
    //         fd = file2;
    //     else if (fd == file2)
    //         fd = file3;
    //     else
    //     {
    //         fd = file1;
    //         all_file_null = 0;
    //     }
    //     line = get_next_line(fd);
    // }
    // close(file1);
    // close(file2);
    // close(file3);
    // ft_printf("\n\nBUFFER_SIZE = %d\n", BUFFER_SIZE);
    return (0);
}
