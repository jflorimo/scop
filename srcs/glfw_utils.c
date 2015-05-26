# include "../includes/scop.h"

void error_callback(int error, const char* description)
{
	(void)error;
	ft_putendl_fd((char *)description, 2);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}