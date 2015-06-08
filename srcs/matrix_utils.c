#include "../includes/scop.h"

t_matrix init_matrix_translation(void)
{

	t_matrix m;

	m.m[0][0] = 1; m.m[0][1] = 0; m.m[0][2] = 0; m.m[0][3] = 0.2;
	m.m[1][0] = 0; m.m[1][1] = 1; m.m[1][2] = 0; m.m[1][3] = 0;
	m.m[2][0] = 0; m.m[2][1] = 0; m.m[2][2] = 1; m.m[2][3] = 0;
	m.m[3][0] = 0; m.m[3][1] = 0; m.m[3][2] = 0; m.m[3][3] = 1;
	return m;
}

t_matrix init_matrix_scale(void)
{
	t_matrix m;

	m.m[0][0] = 0.5; m.m[0][1] = 0; m.m[0][2] = 0; m.m[0][3] = 0;
	m.m[1][0] = 0; m.m[1][1] = 0.5; m.m[1][2] = 0; m.m[1][3] = 0;
	m.m[2][0] = 0; m.m[2][1] = 0; m.m[2][2] = 0.5; m.m[2][3] = 0;
	m.m[3][0] = 0; m.m[3][1] = 0; m.m[3][2] = 0; m.m[3][3] = 1;
	return m;
}
