/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jflorimo <jflorimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/22 13:06:58 by jflorimo          #+#    #+#             */
/*   Updated: 2015/06/23 14:15:03 by jflorimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/scop.h"

void computedatafrominputs(GLFWwindow *window, t_matrix *model, t_scop* scocop)
{
	static int val = 0;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		model->m[3][2] += MOVE_STEP;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		model->m[3][2] -= MOVE_STEP;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		model->m[3][0] += MOVE_STEP;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		model->m[3][0] -= MOVE_STEP;
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		model->m[3][1] += MOVE_STEP;
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		model->m[3][1] -= MOVE_STEP;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		multiply_ptr(init_matrix_rotation_y(MOVE_STEP), model);
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && scocop->state_render == 0)
	{
		glUniform1i(scocop->render_mode, val);
		val = (val + 1) % 2;
		scocop->state_render = 1;
	}
	else if (glfwGetKey(window, GLFW_KEY_T) != GLFW_PRESS)
	{
		scocop->state_render = 0;
	}
}
