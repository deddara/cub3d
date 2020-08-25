/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 05:07:34 by deddara           #+#    #+#             */
/*   Updated: 2020/08/25 14:09:03 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len;
	size_t	start;

	if (!s1 || !s2)
		return (NULL);
	start = (size_t)s1;
	while (*s1)
		s1++;
	len = ((size_t)s1 - start);
	s1 -= ((size_t)s1 - start);
	start = (size_t)s2;
	while (*s2)
		s2++;
	len += ((size_t)s2 - start);
	s2 -= ((size_t)s2 - start);
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	result -= len;
	return (result);
}
