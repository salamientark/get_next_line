#include "get_next_line.h"
#include "./ft_printf/ft_printf.h"

static int	read_block(const int fd, t_block *block)
{
	int	content_len;

	if (!block)
		block = init_block();
	content_len = read(fd, block->content + block->last_pos,
		BUFF_SIZE - block->last_pos);
	if (content_len == -1)
		return (-1);
	block->content_len = content_len;
	block->last_pos = get_end_of_line(block->content);
	return (content_len);
}

static int	read_line(const int fd, t_block **head)
{
	t_block	*head_cp;
	int		line_len;

	line_len = 0;
	if (!(*head))
		(*head) = init_block();
	else
		content_move(*head);
	//while ((*head)->content_len == (*head)->last_pos)
	while ((*head)->last_pos == -1 ||
		((*head)->content_len == (*head)->last_pos))
	{
		head_cp = *head;
		line_len += read_block(fd, *head);
		if ((*head)->next != NULL)
			(*head)->next = head_cp;
	}
	return ((*head)->last_pos);
}

static char	*make_line(int line_len, t_block *head)
{
	char	*line;
	int		buff_index;

	if (line_len == 0)
		return (NULL);
	if (head->content[head->last_pos] == '\n')
		line_len++;
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	line[line_len] = '\0';
	buff_index = head->last_pos;
	while (line_len > 0)
	{
		ft_printf("%c\n", head->content[buff_index]);
		line[--line_len] = head->content[buff_index];
		buff_index--;
		if (buff_index == -1 && line_len > 0)
		{
			head = head->next;
			buff_index = head->last_pos;
		}
	}
	return (line);
}

// Read a line from fd
//	Return :
//		char *  : New_line
//		NULL	: Error or No more line
char	*get_next_line(const int fd)
{
	static t_block	*head;
	int				line_len;
	char			*line;

	if (!fd)
		return (NULL);
	line_len = read_line(fd, &head);
	line = make_line(line_len, head);
	return (line);
}