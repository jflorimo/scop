/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/22 13:15:25 by jflorimo          #+#    #+#             */
/*   Updated: 2015/06/22 13:15:36 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/scop.h"

void exit_error_file(char *str)
{
	printf("File not found: %s (404 NOT FOUND)\n", str);
	exit (0);
}
