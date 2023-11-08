#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 32

typedef struct s_block
{
    char            *content;
    struct s_block  *next;
}                   t_block;

size_t  line_len(size_t block_nbr, size_t last_buffer_len);
t_block	read_block(int fd, t_block textblock, int *line_pos);

int get_next_line(const int fd, char **line);

#endif
