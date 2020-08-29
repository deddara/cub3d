/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:03:26 by deddara           #+#    #+#             */
/*   Updated: 2020/08/29 17:32:14 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"

void	freesher(char **words)
{
	int i;

	i = 0;
	if (words)
	{
		while (words[i])
		{
			free(words[i]);
			i++;
		}
		free(words);
		words = NULL;
	}
}

int		word_counter(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (i != 2)
		return (0);
	return (1);
}

int		check_is_alone(char *line)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			count++;
		i++;
	}
	if ((line[0] == 'R' || line[0] == 'S' || line[0] == 'C'
		|| line[0] == 'F') && count < 2)
		return (0);
	else if (count < 3)
		return (0);
	return (1);
}
