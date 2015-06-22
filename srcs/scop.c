/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 20:18:35 by zion              #+#    #+#             */
/*   Updated: 2015/06/18 14:35:40 by jflorimo         ###   ########.fr       */
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

int main(void)
{
	t_scop* scocop;
	scocop = get_scop();

	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);

//----- http://www.opengl-tutorial.org/
	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

<<<<<<< HEAD
	loadObject("objs/42.obj");
=======
	loadObject("objs/teapot.obj");
>>>>>>> FETCH_HEAD
//-----
	GLuint programID = LoadShaders("shaders/vertexShader", "shaders/fragmentShader");

	GLuint MID = glGetUniformLocation(programID, "M");
	GLuint VID = glGetUniformLocation(programID, "V");
	GLuint PID = glGetUniformLocation(programID, "P");

	t_matrix M;
	M =  init_matrix_translation(0, 0, 0);

	t_matrix V =  init_matrix_translation(0, 0, 0);
	t_matrix P =  init_perspective(60 * M_PI / 180, SCREEN_WIDTH/SCREEN_HEIGHT, 0.1, 100);

<<<<<<< HEAD
	t_matrix trans = init_matrix_translation(0, -3, 30);
	// t_matrix rotate = init_matrix_rotation_y(0.01);
=======
	t_matrix trans = init_matrix_translation(0, -3, 10);
	t_matrix rotate = init_matrix_rotation_y(0.01);
>>>>>>> FETCH_HEAD


	V = multiply(V, trans);

	GLuint Texture = loadBMP_custom("textures/cat.bmp");
	(void)Texture;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		computeDataFromInputs(window, &M);
		glUseProgram(programID);

		glUniformMatrix4fv(VID, 1, GL_FALSE, &V.m[0][0]);
		glUniformMatrix4fv(PID, 1, GL_FALSE, &P.m[0][0]);

<<<<<<< HEAD
		// M = multiply(rotate,M);
=======
		M = multiply(rotate,M);
>>>>>>> FETCH_HEAD

		glUniformMatrix4fv(MID, 1, GL_FALSE, &M.m[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER,scocop->vertex_array_id);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer of-lfset
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scocop->indices_array_id);
		 
		 // Draw the triangles !
		 glDrawElements(
		     GL_TRIANGLES,      // mode
		     scocop->indices_size,    // count
		     GL_UNSIGNED_INT,   // type
		     (void*)0           // element array buffer offset
		 );
		glDisableVertexAttribArray(0);
			

		// Draw the triangle !
//-----
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
