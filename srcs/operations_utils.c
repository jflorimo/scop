/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 16:03:11 by jflorimo          #+#    #+#             */
/*   Updated: 2015/06/23 16:03:13 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"
#include <libft.h>

char *trim(char *str)
{
	char *end;

	while (ft_isspace(*str))
	{
		str++;
	}
	if (*str == 0)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace(*end))
	{
		end--;
	}
	*(end + 1) = 0;
	return (str);
}

void load_file_object(char **s)
{
	if (!ft_strcmp(s[1], "1"))
		load_object("objs/teapot.obj");
	else if (!ft_strcmp(s[1], "2"))
		load_object("objs/teapot2.obj");
	else if (!ft_strcmp(s[1], "3"))
		load_object("objs/petronas.obj");
	else if (!ft_strcmp(s[1], "42"))
		load_object("objs/42.obj");
	else
		exit_error_file_object();
}
