/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 01:34:18 by deddara           #+#    #+#             */
/*   Updated: 2020/07/27 19:54:06 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 50

typedef struct		s_list_g
{
	int				fd;
	char			*rest_buf;
	char			*line_back;
	struct s_list_g	*next;
}					t_lister;

t_lister			*ft_lstnew_gnl(int content);
int					get_next_line(int fd, char **line);
char				*ft_strchr_gnl(const char *s, int c);
char				*ft_strjoin_gnl(char *s1, char *s2);
char				*ft_strdup_gnl(const char *src);
int					clear(t_lister **list, int fd, char *buf, int code);

#endif
