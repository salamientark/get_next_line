/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:35:55 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/23 14:38:56 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Read one text_block and update block param
//	Return :
//		[0;BUFFER_SIZE[	: number of char read from file
//			-1			: ERROR
static ssize_t	read_block(const int fd, t_block **block)
{
	ssize_t	content_len;
	ssize_t	block_len;
	t_block	*tmp;

	tmp = init_block();
	if (!tmp)
		return (-1);
	content_len = read(fd, tmp->content, BUFFER_SIZE);
	if (content_len == -1)
		return (free_all(&tmp), -1);
	tmp->content_len = content_len;
	block_len = 0;
	while (block_len < content_len && tmp->content[block_len] != '\n')
		block_len++;
	tmp->last_pos = block_len;
	tmp->next = *block;
	*block = tmp;
	if (block_len == BUFFER_SIZE)
	{
		tmp->last_pos = -1;
		return (block_len);
	}
	return (block_len + (tmp->content[block_len] == '\n'));
}

// Move after \n content at the begining of buffer
// and update t_block param
static void	content_move(t_block **block)
{
	int	index;
	int	content_len;

	if (!(*block))
		return ;
	index = (*block)->last_pos + 1;
	content_len = (*block)->content_len;
	(*block)->first_pos = index;
	while (index < content_len && (*block)->content[index] != '\n')
		index++;
	(*block)->last_pos = index;
}

// Make a (char *)line from 'head' text_block list of length 'line_len'
//	Return :
//		(char *)	: New_line made
//		NULL		: ERROR or no line to make
static char	*make_line(ssize_t line_len, t_block *head)
{
	char		*line;
	ssize_t		buff_index;

	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	if (head->content_len == 0)
	{
		head = head->next;
		head->last_pos = head->content_len - 1;
	}
	line[line_len] = '\0';
	buff_index = head->last_pos - (head->last_pos == head->content_len);
	while (line_len-- > 0)
	{
		line[line_len] = head->content[buff_index];
		if (buff_index == 0 && line_len > 0)
		{
			head = head->next;
			buff_index = head->content_len;
		}
		buff_index--;
	}
	return (line);
}

// Read one line from file
//	Return :
//		[0;∞[	: number of char in line
//		-1		: ERROR
static char	*read_line(const int fd, t_block **head)
{
	ssize_t	line_len;
	ssize_t	read_result;

	line_len = 0;
	if (*head && (*head)->last_pos > 0 && (*head)->last_pos < BUFFER_SIZE
		&& (*head)->content[(*head)->last_pos] == '\n')
		return (make_line((*head)->last_pos - (*head)->first_pos + 1, (*head)));
	if (*head)
		line_len += (*head)->last_pos - (*head)->first_pos;
	line_len += read_block(fd, head);
	if (line_len <= 0 || !(*head))
		return (NULL);
	while (((*head)->last_pos == -1 && (*head)->content_len == BUFFER_SIZE))
	{
		read_result = read_block(fd, head);
		if (read_result == -1)
			return (NULL);
		line_len += read_result;
	}
	if (line_len <= 0)
		return (NULL);
	return (make_line(line_len, (*head)));
}

// Read a line from fd
//	Return :
//		char *  : New_line
//		NULL	: Error or No more line
char	*get_next_line(const int fd)
{
	static t_gnl_env	*gnl_env;
	t_gnl_env			*tmp_gnl_env;
	char				*line;

	if (fd < 0)
		return (NULL);
	if (!gnl_env)
		gnl_env = init_gnl_env(NULL, fd);
	tmp_gnl_env = gnl_env;
	while (tmp_gnl_env && tmp_gnl_env->fd != fd)
		tmp_gnl_env = tmp_gnl_env->next;
	if (!tmp_gnl_env)
		tmp_gnl_env = init_gnl_env(gnl_env, fd);
	if (!tmp_gnl_env)
		return (NULL);
	line = read_line(fd, &(tmp_gnl_env->head));
	content_move(&(tmp_gnl_env->head));
	if (!line || tmp_gnl_env->head->first_pos > tmp_gnl_env->head->last_pos)
		return (remove_gnl_env(fd, &gnl_env), line);
	free_all(&(tmp_gnl_env->head->next));
	tmp_gnl_env->head->next = NULL;
	return (line);
}
