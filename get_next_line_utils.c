/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:38:04 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/07 20:50:35 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	block->content_len = -1;
	block->last_pos = 0;
	block->next = NULL;
	return (block);
}

// Check if EOL or EOF are in blocks
// Differ from the content len in the way that 
// next line could be in the same block
//	Return :
//	 0 < int < BUFF_SIZE	: end_of_line || end_of_file found
//	 BUFFER_SIZE			: line is longer
int	end_of_line(const char *str)
{
	int	index;

	index = 0;
	while (index < BUFFER_SIZE)
	{
		if (!str[index] || str[index] == '\n')
			return (index);
		index++;
	}
	return (-1);
}

// Move part of the list content at the begining of it
//	 filling the rest with \0
//	Same as memmove then memeset \0 for the end of content
//		Return :
//			void
void	content_move(t_block **block)
{
	int	index;

	index = 0;
	while (index < (BUFFER_SIZE - (*block)->last_pos)
		&& (*block)->content[(*block)->last_pos + index] != '\0')
	{
		(*block)->content[index] = (*block)->content[(*block)->last_pos
			+ index];
		index++;
	}
	(*block)->content_len = index;
	while (index < BUFFER_SIZE)
		(*block)->content[index++] = '\0';
	// (*block)->last_pos = get_char_pos((*block)->content, '\n');
	while (!(!(*block)->last_pos || (*block)->last_pos == '\n')
			&& (*block)->last_pos < BUFFER_SIZE)
		(*block)->last_pos = (*block)->last_pos + 1;
}
