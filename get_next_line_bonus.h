/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:33:50 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/16 20:10:49 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// Chained list of text_blocks
//  content	 : text_content
//  content_len : length of the content
//  last_pos	: \n pos or EOF pos
//  next		: pointer to next block
typedef struct s_block
{
	char			*content;
	int				content_len;
	int				first_pos;
	int				last_pos;
	struct s_block	*next;
}				t_block;

// gnl env containing a t_block for each fd
typedef struct s_gnl_env
{
	int					fd;
	t_block				*head;
	struct s_gnl_env	*next;
}				t_gnl_env;

// UTILS
t_gnl_env	*init_gnl_env(t_gnl_env *gnl_env_head, const int fd);
void		remove_gnl_env(const int fd, t_gnl_env **gnl_env);
t_block		*init_block(void);
void		free_all(t_block **text_block);

// GNL
char		*get_next_line(const int fd);

#endif
