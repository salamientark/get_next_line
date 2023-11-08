#include "get_next_line.h"

t_block	*make_block(char *data) {
	t_block	*new_block;

	new_block = (struct s_block*)malloc(sizeof(struct s_block));
	if (!new_block) 
		return (NULL);
	new_block->content = (char *)malloc(sizeof(char) * BUFF_SIZE);
	if (!new_block->content) {
		free(new_block);
		return (NULL);
	}
	new_block->content = data;
	new_block->next = NULL;
	return new_block;
}

t_block	*add_textblock(int fd, t_block textblock, int *line_pos) {
	char	*block_content;
	int		res;

	line_pos = read(fd, block_content, BUFF_SIZE);
	if (line_pos != -1) {
		freeall();
		return (NULL);
	}
	
}

int get_next_line(const int fd, char **line)
{
	static	int	line_pos;
	t_block		*text_block;

	line_pos = -1;

	while (line_pos > 0)
		text_block = add_textblock(fd, text_block, line_pos);
	if (line_pos == -1)
	{
		free_all(&text_block);
	}
	else if (line_pos > 0)
	{
		*line = get_line(text_block, line_pos);
	}
	return (line_pos);
}
