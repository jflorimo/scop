#include <stdio.h>
# include "../includes/scop.h"

void computeDataFromInputs(GLFWwindow* window, t_matrix* model)
{
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS)
		model->m[3][2] += 0.05;
	if (glfwGetKey( window,GLFW_KEY_DOWN ) == GLFW_PRESS)
		model->m[3][2] -= 0.05;
	if (glfwGetKey( window,GLFW_KEY_RIGHT ) == GLFW_PRESS)
		model->m[3][0] += 0.05;
	if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS)
		model->m[3][0] -= 0.05;
	if (glfwGetKey(window, GLFW_KEY_KP_ADD  ) == GLFW_PRESS)
		model->m[3][1] += 0.05;
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT ) == GLFW_PRESS)
		model->m[3][1] -= 0.05;
}