/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 01:34:18 by deddara           #+#    #+#             */
/*   Updated: 2020/08/25 13:59:06 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

/*
** fd - file descriptor
** rmndr - remainder of readed line from last iteration of GNL function
** rmndr_start - pointer to start of 'rmndr' string (for 'free')
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct	s_list_gnl
{
	int					fd;
	char				*rmndr;
	char				*rmndr_start;
	struct s_list_gnl	*next;
}				t_list_gnl;

int				get_next_line(int fd, char **line);
t_list_gnl		*f_gnl_new(int fd);
t_list_gnl		*f_search_gnl(int fd, t_list_gnl **g_head);

#endif