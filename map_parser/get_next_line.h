/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 01:34:18 by deddara           #+#    #+#             */
/*   Updated: 2020/07/24 21:58:30 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../main.h"

typedef struct		s_list
{
	int				fd;
	char			*rest_buf;
	char			*line_back;
	struct s_list	*next;
}					t_list;
t_list				*ft_lstnew(int content);
int					get_next_line(int fd, char **line);
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strdup(const char *src);
int					clear(t_list **list, int fd, char *buf, int code);

#endif
