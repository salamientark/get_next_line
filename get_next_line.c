/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:53:28 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/09 17:10:48 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Read one text_block and put the result into block->content
// On ERROR or NULL reading (read 0 char)
// free the allocated block
//	Return :
//		[0;BUFFER_SIZE]	: number of char read from file
//			-1			: ERROR
static ssize_t	read_block(const int fd, t_block **block)
{
	int	content_len;

	if (!(*block))
		*block = init_block();
	content_len = read(fd, (*block)->content + (*block)->content_len,
			BUFFER_SIZE - (*block)->content_len) + (*block)->content_len;
	if (content_len <= 0)
	{
		if ((*block)->content)
		{
			free((*block)->content);
			(*block)->content = NULL;
		}
		free((*block));
		(*block) = NULL;
		return (content_len);
	}
	(*block)->content_len = content_len;
	while ((*block)->last_pos < content_len
		&& (*block)->content[(*block)->last_pos] != '\n')
		(*block)->last_pos = (*block)->last_pos + 1;
	if ((*block)->last_pos < (*block)->content_len
		&& (*block)->content[(*block)->last_pos] == '\n')
		return ((*block)->last_pos + 1);
	return ((*block)->last_pos);
}

// Read one line from file store the result as a chained list
// Don't free on error
//	Return :
//		[0;∞[	: number of char in line
//		-1	: ERROR
static ssize_t	read_line(const int fd, t_block **head)
{
	t_block	*tmp_block;
	int		line_len;
	int		read_result;

	line_len = read_block(fd, head);
	if (line_len <= 0)
		return (line_len);
	while (((*head)->last_pos == BUFFER_SIZE))
	{
		tmp_block = init_block();
		read_result = read_block(fd, &tmp_block);
		if (read_result > 0)
		{
			line_len += read_result;
			tmp_block->next = *head;
			*head = tmp_block;
		}
		else if (read_result == -1)
			return (-1);
		else
			return (line_len);
	}
	return (line_len);
}

// Convert chained list (head) to line of len (line_len)a
//	Return :
//		(char *)	: New_line made
//		NULL		: ERROR or no line to make
static char	*make_line(ssize_t line_len, t_block *head)
{
	char	*line;
	ssize_t	buff_index;

	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	if (head->content_len == 0)
		head = head->next;
	line[line_len] = '\0';
	buff_index = head->last_pos;
	if (buff_index == head->content_len)
		buff_index--;
	while (line_len-- > 0)
	{
		line[line_len] = head->content[buff_index];
		if (buff_index == 0 && line_len > 0)
		{
			head = head->next;
			buff_index = BUFFER_SIZE;
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
	ssize_t			line_len;
	char			*line;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	line_len = read_line(fd, &head);
	if (line_len <= 0)
		return (free_all(&head), NULL);
	line = make_line(line_len, head);
	if (!line || head->content_len == 0 || head->last_pos == head->content_len)
		free_all(&head);
	else
	{
		free_all(&(head->next));
		head->next = NULL;
		content_move(&head);
	}
	return (line);
}
