/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:51:47 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/23 14:26:18 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"
#include <stdio.h>

static void print_block(t_block *block)
{
    if (!block)
    {
        ft_printf("Block is NULL\n");
        return ;
    }
    if (!block->content)
        ft_printf("No block_content\n");
    else
        ft_printf("block content: %s\n", block->content);
    if (!block->next)
        ft_printf("next: NULL\n");
    else
        ft_printf("next : %p\n", block->next);
}

void    print_one_block(t_block *block)
{
    ft_printf("--------------------------------------------------\n");
    print_block(block);
    ft_printf("--------------------------------------------------\n");
}

void    print_list(t_block *block)
{
    ft_printf("--------------------------------------------------\n");
    while (block)
    {
        print_block(block);
        block = block->next;
    }
    ft_printf("--------------------------------------------------\n");
}