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
# include "../includes/scop.h"

t_scop *get_scop()
{
	static t_scop scop;

	return (&scop);
}

void init_scocop(t_scop *scop)
{
	scop->state_render = 0;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	scop->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Scocop", NULL, NULL);
	if (!scop->window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(scop->window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(scop->window, key_callback);
}

int main(void)
{
	t_scop* s;
	
	s = get_scop();
	init_scocop(s);	

//----- http://www.opengl-tutorial.org/
	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	//load_object("objs/teapot.obj");
	load_object("objs/teapot2.obj");
	//load_object("objs/42.obj");

//-----
	GLuint programID = load_shaders("shaders/vertexShader", "shaders/fragmentShader");

	GLuint MID = glGetUniformLocation(programID, "M");
	GLuint VID = glGetUniformLocation(programID, "V");
	GLuint PID = glGetUniformLocation(programID, "P");
	s->render_mode = glGetUniformLocation(programID, "renderMode");

	t_matrix M;
	M =  init_matrix_translation(0, 0, 0);

	t_matrix V =  init_matrix_translation(0, 0, 0);
	t_matrix P =  init_perspective(60 * M_PI / 180, SCREEN_WIDTH/SCREEN_HEIGHT, 0.1, 100);

	t_matrix trans = init_matrix_translation(0, -3, 30);

	t_matrix rotate = init_matrix_rotation_y(0.01);



	V = multiply(V, trans);

	GLuint Texture = load_bmp_custom("textures/cat.bmp");
	(void)Texture;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	while (!glfwWindowShouldClose(s->window))
	{
		int width, height;
		glfwGetFramebufferSize(s->window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		computedatafrominputs(s->window, &M, s);
		glUseProgram(programID);

		glUniformMatrix4fv(VID, 1, GL_FALSE, &V.m[0][0]);
		glUniformMatrix4fv(PID, 1, GL_FALSE, &P.m[0][0]);

		M = multiply(rotate,M);


		glUniformMatrix4fv(MID, 1, GL_FALSE, &M.m[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER,s->vertex_array_id);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer of-lfset
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s->indices_array_id);
		 
		 // Draw the triangles !
		 glDrawElements(
		     GL_TRIANGLES,      // mode
		     s->indices_size,    // count
		     GL_UNSIGNED_INT,   // type
		     (void*)0           // element array buffer offset
		 );
		glDisableVertexAttribArray(0);
			

		// Draw the triangle !
//-----
		glfwSwapBuffers(s->window);
		glfwPollEvents();
	}
	glfwDestroyWindow(s->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
