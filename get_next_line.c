#include "get_next_line.h"

// Read one text_block and put the result into block->content
//	Return :
//		[0;BUFF_SIZE[	: number of char read from file
//			-1			: ERROR
static int	read_block(const int fd, t_block **block)
{
	int	content_len;

	if (!(*block))
		(*block) = init_block();
	// content_len = read(fd, (*block)->content + (*block)->last_pos,
	// 	BUFF_SIZE - (*block)->last_pos);
	content_len = read(fd, (*block)->content + (*block)->content_len,
		BUFF_SIZE - (*block)->content_len) + (*block)->content_len;
	if (content_len == -1)
		return (-1);
	(*block)->content_len = content_len;
	(*block)->last_pos = get_char_pos((*block)->content, '\n');
	if ((*block)->last_pos != -1)
		return ((*block)->last_pos);
	return (content_len);
}

// Read one line from file and make a chained list of blocks from it
//	Return :
//		[0;∞[	: number of char in line
//		-1		: ERROR
static int	read_line(const int fd, t_block **head)
{
	t_block	*tmp_block;
	int		line_len;

	line_len = 0;
	// if (!(*head))
	//  	line_len += read_block(fd, head);
	// else
	// 	content_move(head);
	if (*head && (*head)->content)
		content_move(head);
	line_len += read_block(fd, head);
	while ((*head)->last_pos == -1 && (*head)->content_len == BUFF_SIZE)
	{
		tmp_block = init_block();
		line_len += read_block(fd, &tmp_block);
		tmp_block->next = *head;
		*head = tmp_block;
	}
	return (line_len);
}

// Make a (char *)line from 'head' text_block list of length 'line_len'
//	Return :
//		(char *)	: New_line made
//		NULL		: ERROR or no line to make
static char	*make_line(int line_len, t_block *head)
{
	char	*line;
	int		buff_index;

	if (line_len == 0)
		return (NULL);
	// if (head->content[head->last_pos] == '\n')
	// 	line_len++;
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	line[line_len] = '\0';
	buff_index = head->last_pos - 1;
	while (line_len-- > 0)
	{
		// ft_printf("%c - %x\n", head->content[buff_index],
		// 	head->content[buff_index]);
		line[line_len] = head->content[buff_index];
		if (buff_index == 0 && line_len > 0)
		{
			head = head->next;
			buff_index = BUFF_SIZE;
		}
		buff_index--;
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
	if (!line || head->content_len == 0 ||
		(head->content_len < BUFF_SIZE && head->content_len == head->last_pos))
		free_all(&head);
	else
	{
		free_all(&(head->next));
		head->next = NULL;
	}
	return (line);
}