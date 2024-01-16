/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:48:10 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/16 20:11:16 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Init a new gnl_env
t_gnl_env	*init_gnl_env(t_gnl_env *gnl_env_head, const int fd)
{
	t_gnl_env	*new_gnl_env;
	t_gnl_env	*record;

	new_gnl_env = (t_gnl_env *)malloc(sizeof(struct s_gnl_env));
	if (!new_gnl_env)
		return (NULL);
	new_gnl_env->fd = fd;
	new_gnl_env->head = NULL;
	new_gnl_env->next = NULL;
	if (!gnl_env_head)
		return (new_gnl_env);
	record = gnl_env_head;
	while (record->next)
		record = record->next;
	record->next = new_gnl_env;
	return (new_gnl_env);
}

// Remove from gnl_env
void	remove_gnl_env(const int fd, t_gnl_env **gnl_env)
{
	t_gnl_env	*gnl_env_pos;
	t_gnl_env	*tmp_gnl_env;

	if ((*gnl_env)->fd == fd)
	{
		free_all(&((*gnl_env)->head));
	}
	else
	{
		gnl_env_pos = *gnl_env;
		while (gnl_env_pos->next->fd != fd)
			gnl_env_pos = gnl_env_pos->next;
		tmp_gnl_env = gnl_env_pos->next->next;
		free_all(&(gnl_env_pos->next->head));
		gnl_env_pos->next->next = NULL;
		free(gnl_env_pos->next);
		gnl_env_pos->next = tmp_gnl_env;
	}
	if ((*gnl_env)->fd == fd)
	{
		gnl_env_pos = (*gnl_env)->next;
		free((*gnl_env));
		*gnl_env = gnl_env_pos;
	}
}

// Free_all the block and content from text_block to end of it
void	free_all(t_block **text_block)
{
	t_block	*tmp;

	while ((*text_block))
	{
		tmp = (*text_block)->next;
		free((*text_block)->content);
		(*text_block)->content = NULL;
		free((*text_block));
		(*text_block) = NULL;
		(*text_block) = tmp;
	}
}

// Init an empty text_block
//	Return :
//		t_block * : Empty block
t_block	*init_block(void)
{
	t_block	*block;
	int		index;

	block = (t_block *)malloc(sizeof(struct s_block));
	if (!block)
		return (NULL);
	block->content = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!block->content)
	{
		free(block);
		return (NULL);
	}
	index = 0;
	while (index < BUFFER_SIZE)
		block->content[index++] = '\0';
	block->content_len = 0;
	block->last_pos = 0;
	block->first_pos = 0;
	block->next = NULL;
	return (block);
}
