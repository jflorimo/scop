#include <fcntl.h>
#include <stdio.h>
#include <libft.h>
#include "../includes/scop.h"

char *trim(char *str)
{
	char *end;

	// Trim leading space
	while(ft_isspace(*str)) str++;

	if(*str == 0)  // All spaces?
	return str;

	// Trim trailing space
	end = str + ft_strlen(str) - 1;
	while(end > str && ft_isspace(*end)) end--;

	// Write new null terminator
	*(end+1) = 0;

	return str;
}

int loadObject(char *path)
{
	char *line;
	int fd = open(path, O_RDONLY);
	t_list *vertex = new_list();
	t_list *indices = new_list();
	float tab[3];
	int tabf[4];
	int ret;


	if (fd <= 0)
		exit_error_file(path);
	while (get_next_line(fd, &line))
	{
		if (!(trim(line)[0] == '#'))
		{
			if(trim(line)[0] == 'v')
			{
		
				ret = sscanf(line, "v %f %f %f\n", &tab[0], &tab[1], &tab[2]);
				add_elem(vertex, alloc_vec(tab[0], tab[1], tab[2]));
			}
			if(trim(line)[0] == 'f')
			{
				tabf[3] = 0;
				ret = sscanf(line, "f %d %d %d %d\n", &tabf[0], &tabf[1], &tabf[2], &tabf[3]);
				printf("ret: %d\n", ret);
				printf("RECUPv f %d %d %d %d\n", tabf[0], tabf[1], tabf[2], tabf[3]);
				int *ttmp;
				ttmp = malloc(sizeof(int) * 4);
				ttmp[0] = tabf[0] - 1;
				ttmp[1] = tabf[1] - 1;
				ttmp[2] = tabf[2] - 1;
				ttmp[3] = tabf[3] - 1;
				add_elem(indices, &ttmp[0]);
				add_elem(indices, &ttmp[1]);
				add_elem(indices, &ttmp[2]);
				if (ret == 4)
				{
					add_elem(indices, &ttmp[2]);
					add_elem(indices, &ttmp[3]);
					add_elem(indices, &ttmp[0]);
				}
				
			}
		}
	}
	init_object(vertex, indices);
	return (0);
}


void init_object(t_list *vertex, t_list *indices)
{
	t_scop* scocop;

	scocop = get_scop();
	scocop->indices_size = indices->size;

	float *vertex_data;
	vertex_data = malloc(vertex->size * sizeof(float) * 3);


	t_elem *tmp;
	tmp = vertex->first;
	t_vector *vector;
	int i = 0;
	while (tmp)
	{
		vector = (t_vector *)tmp->data;
		vertex_data[i++] = vector->v[0];
		vertex_data[i++] = vector->v[1];
		vertex_data[i++] = vector->v[2];
		tmp = tmp->next;
	}

	glGenBuffers(1, &scocop->vertex_array_id);
	glBindBuffer(GL_ARRAY_BUFFER, scocop->vertex_array_id);
	glBufferData(GL_ARRAY_BUFFER, vertex->size * sizeof(float) * 3, vertex_data, GL_STATIC_DRAW);

	int *indices_data;
	indices_data = malloc(indices->size * sizeof(int));

	tmp = indices->first;
	int entier;
	i = 0;
	while (tmp)
	{
		entier = *((int *)tmp->data);
		indices_data[i++] = entier;
		tmp = tmp->next;
	}

	glGenBuffers(1, &scocop->indices_array_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scocop->indices_array_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size * sizeof(int), indices_data, GL_STATIC_DRAW);

}


