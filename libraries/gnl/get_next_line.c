/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:23:19 by deddara           #+#    #+#             */
/*   Updated: 2020/08/25 16:10:55 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static int	f_exit(char *buf, int fd, t_list_gnl **g_head, int exit_code)
{
	t_list_gnl		*g_tmp;
	t_list_gnl		*g_tmp_2;

	free(buf);
	g_tmp = *g_head;
	if (g_tmp->fd == fd)
		*g_head = g_tmp->next;
	else
	{
		while (g_tmp->next->fd != fd)
			g_tmp = g_tmp->next;
		g_tmp_2 = g_tmp->next;
		g_tmp->next = g_tmp->next->next;
		g_tmp = g_tmp_2;
	}
	free(g_tmp);
	return (exit_code);
}

static int	f_chk_buf(char *buf, t_list_gnl *g_curr, t_list_gnl **g_head)
{
	char			*tmp_ptr;

	if ((tmp_ptr = ft_strchr(buf, '\n')))
	{
		*tmp_ptr = '\0';
		if (!(g_curr->rmndr = ft_strdup(++tmp_ptr)))
			return (f_exit(buf, g_curr->fd, g_head, -1));
		g_curr->rmndr_start = g_curr->rmndr;
	}
	return (tmp_ptr ? 1 : 0);
}

static int	f_read_line(t_list_gnl *g_curr, t_list_gnl **g_head, char **line)
{
	long long			result;
	char				*buf;
	char				*tmp_ptr;

	if (!(buf = (char*)(malloc(sizeof(char) * BUFFER_SIZE + 1))))
		return (f_exit(buf, g_curr->fd, g_head, -1));
	while ((result = read(g_curr->fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[result] = '\0';
		result = f_chk_buf(buf, g_curr, g_head);
		tmp_ptr = *line;
		if (!(*line = ft_strjoin(*line, buf)))
			return (f_exit(buf, g_curr->fd, g_head, -1));
		free(tmp_ptr);
		if (result)
		{
			free(buf);
			return (1);
		}
	}
	return (result == 0 ? f_exit(buf, g_curr->fd, g_head, 0) : \
							f_exit(buf, g_curr->fd, g_head, -1));
}

static int	f_chk_rmndr(t_list_gnl *g_curr, t_list_gnl **g_head, char **line)
{
	char				*tmp_ptr;
	char				*start_pos;

	if (!(*line = ft_strdup("")))
		return (f_exit(NULL, g_curr->fd, g_head, -1));
	if (g_curr->rmndr)
	{
		start_pos = g_curr->rmndr;
		if ((tmp_ptr = ft_strchr(g_curr->rmndr, '\n')))
		{
			*tmp_ptr = '\0';
			g_curr->rmndr = ++tmp_ptr;
		}
		tmp_ptr = *line;
		if (!(*line = ft_strdup(start_pos)))
			return (f_exit(NULL, g_curr->fd, g_head, -1));
		free(tmp_ptr);
		if (start_pos != g_curr->rmndr)
			return (1);
		free(g_curr->rmndr_start);
	}
	return (f_read_line(g_curr, g_head, line));
}

int			get_next_line(int fd, char **line)
{
	static t_list_gnl	*g_head;
	t_list_gnl			*g_curr;
	const long long		buf_size = BUFFER_SIZE;
	char				read_chk[1];

	if (fd < 0 || !line || buf_size < 1 || ((read(fd, read_chk, 0) < 0)))
		return (-1);
	if (!(g_curr = f_search_gnl(fd, &g_head)))
		return (-1);
	return (f_chk_rmndr(g_curr, &g_head, line));
}
