/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:38:04 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/09 21:25:28 by dbaladro         ###   ########.fr       */
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

	block = (t_block *)malloc(sizeof(struct s_block));
	if (!block)
		return (NULL);
	block->content = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!block->content)
	{
		free(block);
		return (NULL);
	}
	block->content_len = 0;
	block->last_pos = 0;
	block->next = NULL;
	return (block);
}

// Maybe could be removed
// Check if EOL or EOF are in blocks
// Differ from the content len in the way that 
// next line could be in the same block
//	Return :
//	 0 < int < BUFF_SIZE	: end_of_line || end_of_file found
//	 BUFFER_SIZE			: line is longer
// ssize_t	end_of_line(const char *str, const ssize_t size)
// {
// 	ssize_t	index;

// 	index = 0;
// 	while (index < size)
// 	{
// 		if (str[index] == '\n')
// 			return (index);
// 		index++;
// 	}
// 	return (index);
// }

// Move block->buffer_content at the beginning of it
// after a line was read
//		Return :
//			void
void	content_move(t_block **block)
{
	int	index;

	index = 0;
	(*block)->last_pos = (*block)->last_pos + 1;
	while (index < ((*block)->content_len - (*block)->last_pos)
		&& (*block)->content[(*block)->last_pos + index] != '\0')
	{
		(*block)->content[index] = (*block)->content[(*block)->last_pos
			+ index];
		index++;
	}
	(*block)->content_len = index;
	(*block)->last_pos = 0;
	while ((*block)->last_pos < (*block)->content_len
		&& (*block)->content[(*block)->last_pos] != '\n')
		(*block)->last_pos = (*block)->last_pos + 1;
}
