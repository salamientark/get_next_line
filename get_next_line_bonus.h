/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dbaladro <dbaladro@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/27 22:01:47 by dbaladro		  #+#	#+#			 */
/*   Updated: 2023/11/27 22:03:26 by madlab           ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

// Chained list of text_blocks
//  content	 : text_content
//  content_len : length of the content
//  last_pos	: \n pos or EOF pos if as one
//  next		: pointer to next block
typedef struct s_block
{
	char			*content;
	int				content_len;
	int				last_pos;
	struct s_block	*next;
}				t_block;

// Chained list of fd_environment.
//	Contain
//	fd 		: file descriptor 
//	buffer	: Associated buffer
//	next	: pointer to next fd_enironment
typedef struct s_gnl_env
{
	int					fd;
	t_block				*buffer;
	struct s_gnl_env	*next;
}				t_gnl_env;

// UTILS
t_block		*init_block(void);
void		free_all_b(t_block **text_block);

t_gnl_env	*init_gnl_env(const int fd);
void		remove_fd(t_gnl_env **gnl_env, const int fd);
void		content_move(t_block **block);

// GNL
char		*get_next_line(const int fd);

#endif
