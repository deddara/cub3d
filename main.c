/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddara <deddara@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 21:22:20 by deddara           #+#    #+#             */
/*   Updated: 2020/08/18 19:49:27 by deddara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "engine.h"
#include <stdio.h>
int             main(int argc, char **argv)
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
	len = ft_strlen(argv[1]);
	len--;
	game();
	return (1);
}