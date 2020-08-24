/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:22:20 by deddara           #+#    #+#             */
/*   Updated: 2020/08/24 16:00:44 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"
#include <stdio.h>

static int	argv_handler(int argc, char **argv)
{
	int len;

	if (argc > 3)
	{
		printf("Too many arguments");
		return (0);
	}
	if (!argv[1])
	{
		printf("no arguments");
		return (0);
	}
	if ((len = ft_strlen(argv[1])) < 4)
	{
		printf("invalid argument");
		return (0);
	}
	len -= 4;
	if (ft_strncmp(&argv[1][len], ".cub", 4) != 0)
	{
		printf("not .cub format");
		return (0);
	}
	return (1);
}

int             main(int argc, char **argv)
{
	if (!argv_handler(argc, argv))
		return (0);
	if (!(game(argv[1])))
		exit(0);
}