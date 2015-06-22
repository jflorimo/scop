/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/22 13:26:24 by jflorimo          #+#    #+#             */
/*   Updated: 2015/06/22 13:26:27 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

t_matrix init_matrix_rotation_x(float x)
{
	t_matrix m;

	m.m[0][0] = 1;
	m.m[1][0] = 0;
	m.m[2][0] = 0;
	m.m[3][0] = 0;
	m.m[0][1] = 0;
	m.m[1][1] = (float)cos(x);
	m.m[2][1] = -(float)sin(x);
	m.m[3][1] = 0;
	m.m[0][2] = 0;
	m.m[1][2] = (float)sin(x);
	m.m[2][2] = (float)cos(x);
	m.m[3][2] = 0;
	m.m[0][3] = 0;
	m.m[1][3] = 0;
	m.m[2][3] = 0;
	m.m[3][3] = 1;
	return (m);
}

t_matrix init_matrix_rotation_y(float y)
{
	t_matrix m;

	m.m[0][0] = (float)cos(y);
	m.m[1][0] = 0;
	m.m[2][0] = (float)sin(y);
	m.m[3][0] = 0;
	m.m[0][1] = 0;
	m.m[1][1] = 1;
	m.m[2][1] = 0;
	m.m[3][1] = 0;
	m.m[0][2] = -(float)sin(y);
	m.m[1][2] = 0;
	m.m[2][2] = (float)cos(y);
	m.m[3][2] = 0;
	m.m[0][3] = 0;
	m.m[1][3] = 0;
	m.m[2][3] = 0;
	m.m[3][3] = 1;
	return (m);
}

t_matrix init_matrix_rotation_z(float z)
{
	t_matrix m;

	m.m[0][0] = (float)cos(z);
	m.m[1][0] = -(float)sin(z);
	m.m[2][0] = 0;
	m.m[3][0] = 0;
	m.m[0][1] = (float)sin(z);
	m.m[1][1] = (float)cos(z);
	m.m[2][1] = 0;
	m.m[3][1] = 0;
	m.m[0][2] = 0;
	m.m[1][2] = 0;
	m.m[2][2] = 1;
	m.m[3][2] = 0;
	m.m[0][3] = 0;
	m.m[1][3] = 0;
	m.m[2][3] = 0;
	m.m[3][3] = 1;
	return (m);
}
