/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_loading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 13:28:08 by jflorimo          #+#    #+#             */
/*   Updated: 2015/06/23 13:28:11 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <libft.h>
#include "../includes/scop.h"

t_rf		*init_data_load_object(char *path)
{
	t_rf	*rf;

	rf = malloc(sizeof(t_rf));
	rf->fd = open(path, O_RDONLY);
	if (rf->fd <= 0)
		exit_error_file(path);
	rf->vertex = new_list();
	rf->indices = new_list();
	return (rf);
}

void		set_indices(t_rf *rf)
{
	if (trim(rf->line)[0] == 'f')
	{
		rf->tabf[3] = 0;
		rf->ret = sscanf(rf->line, "f %d %d %d %d\n", &(rf->tabf[0]),
			&(rf->tabf[1]), &(rf->tabf[2]), &(rf->tabf[3]));
		printf("rf->ret: %d\n", rf->ret);
		printf("RECUPv f %d %d %d %d\n", rf->tabf[0], rf->tabf[1], rf->tabf[2],
			rf->tabf[3]);
		rf->ttmp = malloc(sizeof(int) * 4);
		rf->ttmp[0] = rf->tabf[0] - 1;
		rf->ttmp[1] = rf->tabf[1] - 1;
		rf->ttmp[2] = rf->tabf[2] - 1;
		rf->ttmp[3] = rf->tabf[3] - 1;
		add_elem(rf->indices, &(rf->ttmp[0]));
		add_elem(rf->indices, &(rf->ttmp[1]));
		add_elem(rf->indices, &(rf->ttmp[2]));
		if (rf->ret == 4)
		{
			add_elem(rf->indices, &(rf->ttmp[2]));
			add_elem(rf->indices, &(rf->ttmp[3]));
			add_elem(rf->indices, &(rf->ttmp[0]));
		}
	}
}

int			load_object(char *path)
{
	t_rf	*rf;

	rf = init_data_load_object(path);
	while (get_next_line(rf->fd, &(rf->line)))
	{
		if (!(trim(rf->line)[0] == '#'))
		{
			if (trim(rf->line)[0] == 'v')
			{
				rf->ret = sscanf(rf->line, "v %f %f %f\n", &(rf->tab[0]),
					&(rf->tab[1]), &(rf->tab[2]));
				add_elem(rf->vertex, alloc_vec(rf->tab[0], rf->tab[1],
					rf->tab[2]));
			}
			set_indices(rf);
		}
	}
	init_object(rf->vertex, rf->indices);
	return (0);
}

t_iob		*init_object_data(t_list *vertex, t_list *indices)
{
	t_iob	*iob;
	int		i;

	i = 0;
	iob = malloc(sizeof(t_iob));
	iob->scocop = get_scop();
	iob->scocop->indices_size = indices->size;
	iob->vertex_data = malloc(vertex->size * sizeof(float) * 3);
	iob->tmp = vertex->first;
	while (iob->tmp)
	{
		iob->vector = (t_vector *)iob->tmp->data;
		iob->vertex_data[i++] = iob->vector->v[0];
		iob->vertex_data[i++] = iob->vector->v[1];
		iob->vertex_data[i++] = iob->vector->v[2];
		iob->tmp = iob->tmp->next;
	}
	return (iob);
}

void		init_object(t_list *vertex, t_list *indices)
{
	t_iob	*iob;
	int		*indices_data;
	int		entier;
	int		i;

	i = 0;
	iob = init_object_data(vertex, indices);
	glGenBuffers(1, &(iob->scocop->vertex_array_id));
	glBindBuffer(GL_ARRAY_BUFFER, iob->scocop->vertex_array_id);
	glBufferData(GL_ARRAY_BUFFER, vertex->size * sizeof(float) * 3,
		iob->vertex_data, GL_STATIC_DRAW);
	indices_data = malloc(indices->size * sizeof(int));
	iob->tmp = indices->first;
	while (iob->tmp)
	{
		entier = *((int *)iob->tmp->data);
		indices_data[i++] = entier;
		iob->tmp = iob->tmp->next;
	}
	glGenBuffers(1, &(iob->scocop->indices_array_id));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iob->scocop->indices_array_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size * sizeof(int),
		indices_data, GL_STATIC_DRAW);
}
