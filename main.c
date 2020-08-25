/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:22:20 by deddara           #+#    #+#             */
/*   Updated: 2020/08/25 17:14:45 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"

static int	argv_handler(int argc, char **argv)
{
	int len;

	if (argc > 3)
	{
		ft_putstr_fd("Too many arguments", 0);
		return (0);
	}
	if (!argv[1])
	{
		ft_putstr_fd("no arguments", 0);
		return (0);
	}
	if ((len = ft_strlen(argv[1])) < 4)
	{
		ft_putstr_fd("invalid argument", 0);
		return (0);
	}
	len -= 4;
	if (ft_strncmp(&argv[1][len], ".cub", 4) != 0)
	{
		ft_putstr_fd("not .cub format", 0);
		return (0);
	}
	return (1);
}

int			main(int argc, char **argv)
{
	if (!argv_handler(argc, argv))
		return (0);
	if (!(game(argv[1])))
		exit(0);
	return (1);
}
