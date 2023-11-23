/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:38:04 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/23 16:19:04 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Init an empty text_block
//  Return :
//      t_block * : Empty block
t_block *init_block()
{
    t_block *block;

    block = (t_block *)malloc(sizeof(struct s_block));
    if (!block)
        return (NULL);
    block->content = (char *)malloc(sizeof(char) * BUFF_SIZE);
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

// Check if str contain '\n' or if str is last line
//  Return :
//   -1     : Neither EOF or \n found
//    int   : pos of \n
int get_end_of_line(const char *str)
{
    int index;

    index = 0;
    while (str[index] && index < BUFF_SIZE)
    {
        if (str[index] == '\n')
            return (index);
        index++;
    }
    return (-1);
    // return (index);
}

// Move part of the list content at the begining of it
//   filling the rest with \0
//  Same as memmove then memeset \0 for the end of content
//      Return :
//          void
void    content_move(t_block *block)
{
    int index;

    index = 0;
    while (index < block->last_pos)
    {
        block->content[index] = block->content[block->last_pos + index];
        index++;
    }
    while (index < BUFF_SIZE)
        block->content[index++] = '\0';
}