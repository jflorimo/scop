/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 20:18:35 by zion              #+#    #+#             */
/*   Updated: 2015/06/23 16:20:46 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include "../includes/scop.h"

t_scop				*get_scop(void)
{
	static t_scop	scop;

	return (&scop);
}

void				init_scocop(t_scop *s)
{
	s->state_render = 0;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	s->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Scocop",
		NULL, NULL);
	if (!s->window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(s->window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(s->window, key_callback);
	glGenVertexArrays(1, &(s->vertex_array_id));
	glBindVertexArray(s->vertex_array_id);
}

void				init_mvp(t_scop *s)
{
	s->program_id = load_shaders("shaders/vertexShader",
		"shaders/fragmentShader");
	s->model_id = glGetUniformLocation(s->program_id, "M");
	s->vue_id = glGetUniformLocation(s->program_id, "V");
	s->projection_id = glGetUniformLocation(s->program_id, "P");
	s->render_mode = glGetUniformLocation(s->program_id, "renderMode");
	s->model = init_matrix_translation(0, 0, 0);
	s->vue = init_matrix_translation(0, 0, 0);
	s->projection = init_perspective(60 * M_PI / 180,
		SCREEN_WIDTH / SCREEN_HEIGHT, 0.1, 100);
	s->trans = init_matrix_translation(0, -3, 30);
	s->rotate = init_matrix_rotation_y(0.01);
	s->vue = multiply(s->vue, s->trans);
	s->texture = load_bmp_custom("textures/cat.bmp");
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void				main_loop(t_scop *s)
{
	glfwGetFramebufferSize(s->window, &(s->width), &(s->height));
	glViewport(0, 0, s->width, s->height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	computedatafrominputs(s->window, &(s->model), s);
	glUseProgram(s->program_id);
	glUniformMatrix4fv(s->vue_id, 1, GL_FALSE, &(s->vue.m[0][0]));
	glUniformMatrix4fv(s->projection_id, 1, GL_FALSE,
		&(s->projection.m[0][0]));
	s->model = multiply(s->rotate, s->model);
	glUniformMatrix4fv(s->model_id, 1, GL_FALSE, &(s->model.m[0][0]));
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, s->vertex_array_id);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s->indices_array_id);
	glDrawElements(GL_TRIANGLES, s->indices_size, GL_UNSIGNED_INT,
		(void*)0);
	glDisableVertexAttribArray(0);
	glfwSwapBuffers(s->window);
	glfwPollEvents();
}

int					main(int argc, char **argv)
{
	t_scop			*s;

	s = get_scop();
	init_scocop(s);
	if (argc == 1)
		load_object("objs/42.obj");
	else
		load_file_object(argv);
	init_mvp(s);
	while (!glfwWindowShouldClose(s->window))
	{
		main_loop(s);
	}
	glfwDestroyWindow(s->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
