/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/20 20:18:45 by zion              #+#    #+#             */
/*   Updated: 2015/06/23 16:15:29 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <libft.h>
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <math.h>
# define BMP_HEADER_SIZE 54
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define MOVE_STEP 0.1

void				error_callback(int error, const char *description);
void				key_callback(GLFWwindow *window, int key, int scancode,
	int action, int mods);
GLuint				load_shaders(const char *vertex_file_path,
	const char *fragment_file_path);
typedef struct		s_bmp
{
	unsigned char	header[54];
	unsigned int	data_pos;
	unsigned int	width;
	unsigned int	height;
	unsigned int	image_size;
	unsigned char	*data;
}					t_bmp;
typedef struct		s_matrix
{
	float			m[4][4];
}					t_matrix;
typedef struct		s_vector
{
	float			v[3];
}					t_vector;
typedef struct		s_scop
{
	GLuint			vertex_array_id;
	GLuint			indices_array_id;
	GLint			render_mode;
	int				state_render;
	int				indices_size;
	GLFWwindow		*window;
	GLuint			program_id;
	GLuint			model_id;
	GLuint			vue_id;
	GLuint			projection_id;
	t_matrix		model;
	t_matrix		vue;
	t_matrix		projection;
	t_matrix		trans;
	t_matrix		rotate;
	GLuint			texture;
	int				width;
	int				height;
}					t_scop;
typedef struct		s_rf
{
	char			*line;
	int				fd;
	t_list			*vertex;
	t_list			*indices;
	float			tab[3];
	int				tabf[4];
	int				ret;
	int				*ttmp;
}					t_rf;
typedef struct		s_iob
{
	t_scop			*scocop;
	t_elem			*tmp;
	t_vector		*vector;
	float			*vertex_data;
}					t_iob;
typedef struct		s_bmp_init
{
	int				fd;
	int				rt;
	GLuint			texture_id;
}					t_bmp_init;
typedef struct		s_shad_init
{
	GLuint			vertex_shader_id;
	GLuint			fragment_shader_id;
	GLuint			program_id;
	GLint			result;
	int				info_log_length;
	char			*vertex_code;
	char			*fragment_code;
	char			*line;
	int				fd;
	char const		*vertex_source_pointer;
	char const		*fragment_source_pointer;
	char			program_shader_error_message[1024];
	char			vertex_shader_error_message[1024];
	char			fragment_shader_error_message[1024];
}					t_shad_init;
char				*trim(char *str);
t_scop				*get_scop();
t_matrix			init_matrix_translation(float x, float y, float z);
t_matrix			init_matrix_scale(float x, float y, float z);
t_matrix			init_perspective(float fov, float aspect, float z_near,
	float z_far);
t_matrix			multiply(t_matrix data1, t_matrix data2);
void				multiply_ptr(t_matrix data1, t_matrix *data2);
t_matrix			init_matrix_rotation_x(float x);
t_matrix			init_matrix_rotation_y(float y);
t_matrix			init_matrix_rotation_z(float z);
GLuint				load_bmp_custom(const char *imagepath);
t_vector			init_vec(float x, float y, float z);
t_vector			*alloc_vec(float x, float y, float z);
void				computedatafrominputs(GLFWwindow *window, t_matrix *model,
	t_scop *scocop);
int					load_object(char *path);
void				init_object(t_list *vertex, t_list *indices);
void				exit_error_file(char *str);
void				exit_error_file_format(void);
void				exit_error_file_object(void);
void				load_file_object(char **s);

#endif
