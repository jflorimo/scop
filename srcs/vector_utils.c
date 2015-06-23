/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 14:49:59 by jflorimo          #+#    #+#             */
/*   Updated: 2015/06/23 14:50:02 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

t_vector		init_vec(float x, float y, float z)
{
	t_vector	v;

	v.v[0] = x;
	v.v[1] = y;
	v.v[2] = z;
	return (v);
}

t_vector		*alloc_vec(float x, float y, float z)
{
	t_vector	*v;

	v = malloc(sizeof(t_vector));
	if (!v)
		return (0);
	v->v[0] = x;
	v->v[1] = y;
	v->v[2] = z;
	return (v);
}
