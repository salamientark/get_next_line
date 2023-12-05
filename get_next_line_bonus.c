/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:35:55 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/05 22:34:50 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"

// Read one text_block and put the result into block->content
//	Return :
//		[0;BUFF_SIZE[	: number of char read from file
//			-1			: ERROR
static int	read_block(const int fd, t_block **block)
{
	int	content_len;

	if (!(*block))
		(*block) = init_block();
	content_len = read(fd, (*block)->content + (*block)->content_len,
			BUFF_SIZE - (*block)->content_len) + (*block)->content_len;
	if (content_len == -1)
		return (-1);
	(*block)->content_len = content_len;
	(*block)->last_pos = get_char_pos((*block)->content, '\n');
	if ((*block)->last_pos > 0)
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
	if (*head && (*head)->content)
		content_move(head);
	line_len += read_block(fd, head);
	if (line_len == -1)
		return (-1);
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

	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	if (head->content_len == 0)
	{
		head = head->next;
		head->last_pos = BUFF_SIZE - 1;
	}
	line[line_len] = '\0';
	buff_index = head->last_pos;
	while (line_len-- > 0)
	{
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
	static t_gnl_env	*gnl_env;
	t_gnl_env			tmp_gnl_env;
	int				    line_len;
	char			    *line;

	if (fd < 0 || BUFF_SIZE == 0)
		return (NULL);
	tmp_gnl_env = gnl_env;
	while (tmp_gnl_env && tmp_gnl_env->fd != fd)
		tmp_gnl_env = tmp_gnl_env->next;
	if (!tmp_gnl_env)
		tmp_gnl_env = init_gnl_env(fd, gnl_env);
	line_len = read_line(fd, &(tmp_gnl_env->head));
	if (line_len <= 0)
		return (free_all(&head), NULL);
	line = make_line(line_len, head);
	if (!line || head->content_len == 0 || head->last_pos == (BUFF_SIZE - 1))
		remove_gnl_env(fd, &gnl_env);
	else
	{
		free_all(&(head->next));
		head->next = NULL;
	}
	return (line);
}
