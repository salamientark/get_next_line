/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:38:04 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/27 18:52:13 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Free_all the block and content from text_block to end of it
void    free_all(t_block **text_block)
{
    t_block *tmp;

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
//  Return :
//      t_block * : Empty block
t_block *init_block()
{
    t_block *block;
    int     index;

    block = (t_block *)malloc(sizeof(struct s_block));
    if (!block)
        return (NULL);
    block->content = (char *)malloc(sizeof(char) * BUFF_SIZE);
    if (!block->content)
    {
        free(block);
        return (NULL);
    }
    index = 0;
    while (index < BUFF_SIZE)
        block->content[index++] = '\0';
    block->content_len = 0;
    block->last_pos = 0;
    block->next = NULL;
    return (block);
}

int get_char_pos(const char *str, int c)
{
    int index;

    index = 0;
    while (index < BUFF_SIZE)
    {
        if (str[index] == c)
            return (index + 1);
        index++;
    }
    return (-1);
}

// Check if str contain \n or if str is last line
//  Return :
//   -1     : Neither EOF or \n found
//    int   : pos of \n
int get_end_of_line(const char *str)
{
    int index;

    index = 0;
    while (index < BUFF_SIZE && str[index] != '\0')
    {
        if (str[index] == '\n')
            return (index + 1);
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
void    content_move(t_block **block)
{
    int index;

    index = 0;
    while (index < (BUFF_SIZE - (*block)->last_pos))
    {
        (*block)->content[index] = (*block)->content[(*block)->last_pos + index];
        index++;
    }
    // (*block)->content_len = BUFF_SIZE - index;
    (*block)->content_len = index;
    // (*block)->content_len = get_char_pos((*block)->content, '\0');
    // if ((*block)->content_len == -1)
    //     (*block)->content_len = BUFF_SIZE;
    while (index < BUFF_SIZE)
        (*block)->content[index++] = '\0';
    (*block)->last_pos = get_char_pos((*block)->content, '\n');
}