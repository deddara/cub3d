/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:23:19 by deddara           #+#    #+#             */
/*   Updated: 2020/07/27 19:45:56 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_lister	*get_fd(t_lister **list, int fd)
{
	t_lister *tmp;

	if ((*list) == NULL)
		return ((*list = ft_lstnew_gnl(fd)));
	tmp = (*list);
	while ((tmp->fd != fd && tmp->next != 0))
		tmp = tmp->next;
	if (tmp->fd == fd)
		return (tmp);
	else
	{
		tmp->next = ft_lstnew_gnl(fd);
		return (tmp->next);
	}
}

static char	*check_buf(t_lister *list, char **line)
{
	char *new_liner;
	char *new_line;

	if ((list)->rest_buf == NULL)
	{
		if (!(new_liner = (char *)malloc(sizeof(char) * 1)))
			return (NULL);
		new_liner[0] = '\0';
		return (new_liner);
	}
	if ((new_line = ft_strchr_gnl((list)->rest_buf, '\n')))
	{
		*new_line++ = '\0';
		if (!((*line) = ft_strdup_gnl((list)->rest_buf)))
			return (NULL);
		new_line = ft_strdup_gnl(new_line);
		free((list)->rest_buf);
		(list)->rest_buf = new_line;
		return (*line);
	}
	(*line) = (list)->rest_buf;
	(list)->rest_buf = NULL;
	return (*line);
}

static int	reader_mn(char *buf, t_lister *list, char **line)
{
	char *new_line;

	if ((new_line = ft_strchr_gnl(buf, '\n')))
	{
		*new_line++ = '\0';
		if (!((list)->rest_buf = ft_strdup_gnl(new_line)))
			return (0);
	}
	list->line_back = (*line);
	if (!((*line) = ft_strjoin_gnl(*line, buf)))
		return (0);
	free(list->line_back);
	list->line_back = NULL;
	return (1);
}

static int	read_line(t_lister **list, char **line, int fd, t_lister *ptr)
{
	const long long		buff_size = BUFFER_SIZE;
	char				*buf;
	long long			ret;

	ret = 0;
	if (!(buf = (char*)malloc(sizeof(char) * buff_size + 1)))
		return (clear(list, fd, buf, -1));
	while (((ptr)->rest_buf == NULL) && (ret = read(fd, buf, buff_size)))
	{
		if (ret < 0)
			return (clear(list, fd, buf, -1));
		buf[ret] = '\0';
		if (!reader_mn(buf, ptr, line))
			return (clear(list, fd, buf, -1));
	}
	if (ret < buff_size && ((ptr)->rest_buf) == NULL)
		return (clear(list, fd, buf, 0));
	free(buf);
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static t_lister	*list;
	t_lister		*list_ptr;
	const long long	buff_size = BUFFER_SIZE;
	char			test[1];

	if (fd < 0 || buff_size <= 0 || !line || read(fd, test, 0) < 0 ||
	!(list_ptr = get_fd(&list, fd)))
		return (-1);
	if (!((*line) = check_buf(list_ptr, line)))
		return (clear(&(list), fd, NULL, -1));
	return (read_line(&(list), line, fd, list_ptr));
}
