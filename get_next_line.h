#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 32

typedef struct s_block
{
    char            *content;
    int             content_len;
    int             last_pos;
    struct s_block  *next;
}                   t_block;

// UTILS
t_block *init_block();
int     get_end_of_line(const char *str);
void    content_move(t_block **block);
void    free_all(t_block *text_block);

// GNL
char	*get_next_line(const int fd);

#endif
