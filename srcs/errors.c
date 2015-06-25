/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/22 13:15:25 by jflorimo          #+#    #+#             */
/*   Updated: 2015/06/23 16:07:39 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/scop.h"

void exit_error_file(char *str)
{
	printf("File not found: %s (404 NOT FOUND)\n", str);
	exit (0);
}

void exit_error_file_format(void)
{
	printf("File error (NOT BMP)\n");
	exit (0);
}

void exit_error_file_object(void)
{
	printf("File error object\n");
	exit (0);
}
