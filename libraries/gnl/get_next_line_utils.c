/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 17:24:24 by deddara           #+#    #+#             */
/*   Updated: 2020/08/24 16:39:41 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			clear(t_lister **list, int fd, char *buf, int code)
{
	t_lister	*tmp;
	t_lister	*var;

	if (*list)
	{
		tmp = *list;
		if (tmp->fd == fd)
			*list = tmp->next;
		else
		{
			while (tmp->next->fd != fd)
				tmp = tmp->next;
			var = tmp->next;
			tmp->next = var->next;
			tmp = var;
		}
		free(tmp->rest_buf);
		free(tmp->line_back);
		free(tmp);
	}
	free(buf);
	if (code == -1)
		return (-1);
	return (0);
}

char		*ft_strdup_gnl(const char *src)
{
	char	*result;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\0')
		i++;
	if(!(result = (char*)malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (src[i])
	{
		result[i] = src[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

t_lister	*ft_lstnew_gnl(int content)
{
	t_lister *var;

	var = malloc(sizeof(t_lister));
	if (!var)
		return (0);
	var->fd = content;
	var->next = NULL;
	var->rest_buf = NULL;
	var->line_back = NULL;
	return (var);
}

char		*ft_strchr_gnl(const char *s, int c)
{
	int i;

	i = 0;
	if (!s)
		return (NULL);
	if (s[0] == '\0' && s[0] == (unsigned char)c)
		return ((char*)&s[0]);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char*)&s[i]);
		else if (s[i + 1] == (unsigned char)c)
			return ((char*)&s[i + 1]);
		i++;
	}
	return (NULL);
}

char		*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	if (!(result = (char*)malloc((i + j) + 1)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}
