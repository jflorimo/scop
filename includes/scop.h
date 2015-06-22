/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 20:18:45 by zion              #+#    #+#             */
/*   Updated: 2015/06/22 11:56:32 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

// #ifdef __APPLE__
// # define __gl_h_
// # define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
// #endif

# include <libft.h>
// # define GLFW_INCLUDE_GLU
// # define GL_GLEXT_PROTOTYPES
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <math.h>
# define BMP_HEADER_SIZE 54
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define MOVE_STEP 0.1 


void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
GLuint LoadShaders(const char *vertex_file_path,const char *fragment_file_path);

typedef struct		s_bmp
{
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;
}					t_bmp;

typedef struct		s_matrix
{
	float	m[4][4];
}					t_matrix;

typedef struct		s_vector
{
	float	v[3];
}					t_vector;

typedef struct		s_scop
{
	GLuint vertex_array_id;
	GLuint indices_array_id;
	int			indices_size;
}					t_scop;

t_scop *get_scop();

t_matrix init_matrix_translation(float x, float y, float z);
t_matrix init_matrix_scale(float x, float y, float z);
t_matrix init_perspective(float fov, float aspect, float z_near, float z_far);
t_matrix multiply(t_matrix data1, t_matrix data2);
void	 multiply_ptr(t_matrix data1, t_matrix *data2);
t_matrix init_matrix_rotation_x(float x);
t_matrix init_matrix_rotation_y(float y);
t_matrix init_matrix_rotation_z(float z);

GLuint loadBMP_custom(const char * imagepath);
t_vector init_vec(float x, float y, float z);
t_vector *alloc_vec(float x, float y, float z);
void computeDataFromInputs(GLFWwindow* window, t_matrix* model);
int loadObject(char *path);
void init_object(t_list *vertex, t_list *indices);
void exit_error_file(char *str);

#endif
