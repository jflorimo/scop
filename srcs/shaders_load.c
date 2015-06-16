#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include "../includes/scop.h"

GLuint LoadShaders(const char *vertex_file_path,const char *fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	char* VertexShaderCode;
	char *line;
	int filedescriptor = open(vertex_file_path, O_RDONLY);
	get_next_line(filedescriptor, &line);
	VertexShaderCode = ft_strjoin("", line);
	while(get_next_line(filedescriptor, &line))
	{
		VertexShaderCode = ft_strjoin(VertexShaderCode, "\n");
		VertexShaderCode = ft_strjoin(VertexShaderCode, line);
	}


	// Read the Fragment Shader code from the file
	char *FragmentShaderCode;
	filedescriptor = open(fragment_file_path, O_RDONLY);
	get_next_line(filedescriptor, &line);
	FragmentShaderCode = ft_strjoin("", line);
	while(get_next_line(filedescriptor, &line))
	{
		FragmentShaderCode = ft_strjoin(FragmentShaderCode, "\n");
		FragmentShaderCode = ft_strjoin(FragmentShaderCode, line);
	}


	GLint Result = GL_FALSE;
	int InfoLogLength;
	
	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode;

	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	char vertex_shader_error_message[1024];
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, vertex_shader_error_message);
	write(2, vertex_shader_error_message, InfoLogLength);
	// printf("VECTEX:%s\n", vertex_shader_error_message);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode;
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	char fragment_shader_error_message[1024];
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, fragment_shader_error_message);
	write(2, fragment_shader_error_message, InfoLogLength);

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	char program_shader_error_message[1024];
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, program_shader_error_message);
	// printf("PROGRAM:%s\n", program_shader_error_message);
	write(2, program_shader_error_message, InfoLogLength);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;

}