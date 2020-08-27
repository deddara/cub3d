/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:22:20 by deddara           #+#    #+#             */
/*   Updated: 2020/08/27 13:23:58 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"
#include <sys/types.h>
#include <unistd.h>

int			shut_down_music(void)
{
	char	*line;
	int		fd;
	char	*kill;

	if ((fd = open("processes.txt", O_RDONLY)) < 0)
		return (0);
	get_next_line(fd, &line);
	kill = ft_strjoin("kill ", line);
	free_line(line);
	system(kill);
	free(kill);
	system("rm processes.txt");
	return (1);
}

static int	argv_handler_add(int argc, char **argv)
{
	if (argc > 3)
	{
		ft_putstr_fd("Too many arguments", 0);
		return (0);
	}
	if (argc == 3 && (ft_strncmp("--save", argv[2], ft_strlen(argv[2])) != 0\
	|| ft_strncmp("--save", argv[2], 6) != 0))
	{
		ft_putstr_fd("invalid second argument", 0);
		return (0);
	}
	return (1);
}

static int	argv_handler(int argc, char **argv)
{
	int len;

	if (!argv_handler_add(argc, argv))
		return (0);
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

#ifdef BONUS
int			main(int argc, char **argv)
{
	system("afplay test.mp3 &");
	system("ps -a | grep \"afplay test.mp3\" | sed 's/[ \\t]*\\([0-9]\\{1,\\}\\).*/\\1/' >> processes.txt &");
	if (!argv_handler(argc, argv))
		return (0);
	if (!(game(argv, argc)))
	{
		shut_down_music();
		exit(0);
	}
	shut_down_music();
	return (1);
}

#else

int			main(int argc, char **argv)
{
	if (!argv_handler(argc, argv))
		return (0);
	if (!(game(argv, argc)))
		exit(0);
	return (1);
}
#endif