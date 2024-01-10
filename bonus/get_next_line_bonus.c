/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:35:55 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/06 16:01:45 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"

// Read one text_block and put the result into block->content
//	Return :
//		[0;BUFFER_SIZE[	: number of char read from file
//			-1			: ERROR
static int	read_block(const int fd, t_block **block)
{
	int	content_len;

	if (!(*block))
		(*block) = init_block();
	content_len = read(fd, (*block)->content + (*block)->content_len,
			BUFFER_SIZE - (*block)->content_len) + (*block)->content_len;
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
	while ((*head)->last_pos == -1 && (*head)->content_len == BUFFER_SIZE)
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
		head->last_pos = BUFFER_SIZE - 1;
	}
	line[line_len] = '\0';
	buff_index = head->last_pos;
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
	static t_gnl_env	*gnl_env;
	t_gnl_env			*tmp_gnl_env;
	int				    line_len;
	char			    *line;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	if (!gnl_env)
		gnl_env = init_gnl_env(NULL, fd);
	tmp_gnl_env = gnl_env;
	while (tmp_gnl_env && tmp_gnl_env->fd != fd)
		tmp_gnl_env = tmp_gnl_env->next;
	if (!tmp_gnl_env)
		tmp_gnl_env = init_gnl_env(gnl_env, fd);
	line_len = read_line(fd, &(tmp_gnl_env->head));
	if (line_len <= 0)
		return (remove_gnl_env(fd, &gnl_env), NULL);
	line = make_line(line_len, tmp_gnl_env->head);
	if (!line || tmp_gnl_env->head->content_len == 0 
		|| tmp_gnl_env->head->last_pos == (BUFFER_SIZE - 1))
		remove_gnl_env(fd, &gnl_env);
	else
	{
		free_all(&(tmp_gnl_env->head->next));
		tmp_gnl_env->head->next = NULL;
	}
	return (line);
}
