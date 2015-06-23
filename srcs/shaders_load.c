/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 15:43:58 by jflorimo          #+#    #+#             */
/*   Updated: 2015/06/23 15:44:00 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include "../includes/scop.h"

t_shad_init		*init_shad_data(void)
{
	t_shad_init *t;

	t = malloc(sizeof(t_shad_init));
	t->vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	t->fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	t->program_id = glCreateProgram();
	t->result = GL_FALSE;
	return (t);
}

void			load_part_one(t_shad_init *t, const char *v, const char *f)
{
	t->fd = open(v, O_RDONLY);
	get_next_line(t->fd, &(t->line));
	t->vertex_code = ft_strjoin("", t->line);
	while (get_next_line(t->fd, &(t->line)))
	{
		t->vertex_code = ft_strjoin(t->vertex_code, "\n");
		t->vertex_code = ft_strjoin(t->vertex_code, t->line);
	}
	t->fd = open(f, O_RDONLY);
	get_next_line(t->fd, &(t->line));
	t->fragment_code = ft_strjoin("", t->line);
	while (get_next_line(t->fd, &(t->line)))
	{
		t->fragment_code = ft_strjoin(t->fragment_code, "\n");
		t->fragment_code = ft_strjoin(t->fragment_code, t->line);
	}
	printf("Compiling shader : %s\n", v);
	t->vertex_source_pointer = t->vertex_code;
	glShaderSource(t->vertex_shader_id, 1, &(t->vertex_source_pointer), NULL);
	glCompileShader(t->vertex_shader_id);
}

void			load_part_two(t_shad_init *t, const char *fragment_file_path)
{
	glGetShaderiv(t->vertex_shader_id, GL_COMPILE_STATUS, &t->result);
	glGetShaderiv(t->vertex_shader_id, GL_INFO_LOG_LENGTH, &t->info_log_length);
	glGetShaderInfoLog(t->vertex_shader_id, t->info_log_length, NULL,
		t->vertex_shader_error_message);
	write(2, t->vertex_shader_error_message, t->info_log_length);
	printf("Compiling shader : %s\n", fragment_file_path);
	t->fragment_source_pointer = t->fragment_code;
	glShaderSource(t->fragment_shader_id, 1, &(t->fragment_source_pointer),
		NULL);
	glCompileShader(t->fragment_shader_id);
	glGetShaderiv(t->fragment_shader_id, GL_COMPILE_STATUS, &t->result);
	glGetShaderiv(t->fragment_shader_id, GL_INFO_LOG_LENGTH,
		&t->info_log_length);
	glGetShaderInfoLog(t->fragment_shader_id, t->info_log_length, NULL,
		t->fragment_shader_error_message);
	write(2, t->fragment_shader_error_message, t->info_log_length);
}

GLuint			load_shaders(const char *vertex_file_path,
	const char *fragment_file_path)
{
	t_shad_init	*t;

	t = init_shad_data();
	load_part_one(t, vertex_file_path, fragment_file_path);
	load_part_two(t, fragment_file_path);
	printf("Linking program\n");
	glAttachShader(t->program_id, t->vertex_shader_id);
	glAttachShader(t->program_id, t->fragment_shader_id);
	glLinkProgram(t->program_id);
	glGetProgramiv(t->program_id, GL_LINK_STATUS, &t->result);
	glGetProgramiv(t->program_id, GL_INFO_LOG_LENGTH, &t->info_log_length);
	glGetProgramInfoLog(t->program_id, t->info_log_length, NULL,
		t->program_shader_error_message);
	write(2, t->program_shader_error_message, t->info_log_length);
	glDeleteShader(t->vertex_shader_id);
	glDeleteShader(t->fragment_shader_id);
	return (t->program_id);
}
