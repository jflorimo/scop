#include "../includes/scop.h"

t_matrix init_matrix_translation(float x, float y, float z)
{

	t_matrix m;

	m.m[0][0] = 1; m.m[1][0] = 0; m.m[2][0] = 0; m.m[3][0] = x;
	m.m[0][1] = 0; m.m[1][1] = 1; m.m[2][1] = 0; m.m[3][1] = y;
	m.m[0][2] = 0; m.m[1][2] = 0; m.m[2][2] = 1; m.m[3][2] = z;
	m.m[0][3] = 0; m.m[1][3] = 0; m.m[2][3] = 0; m.m[3][3] = 1;
	return m;
}

t_matrix init_matrix_scale(float x, float y, float z)
{
	t_matrix m;

	m.m[0][0] = x; m.m[1][0] = 0; m.m[2][0] = 0; m.m[3][0] = 0;
	m.m[0][1] = 0; m.m[1][1] = y; m.m[2][1] = 0; m.m[3][1] = 0;
	m.m[0][2] = 0; m.m[1][2] = 0; m.m[2][2] = z; m.m[3][2] = 0;
	m.m[0][3] = 0; m.m[1][3] = 0; m.m[2][3] = 0; m.m[3][3] = 1;
	return m;
}

t_matrix	init_perspective(float fov, float aspect, float z_near, float z_far)
{
	t_matrix	res;
	float	tan_half_fov;
	float	z_range;

	tan_half_fov = tanf(fov / 2.0f);
	z_range = z_near - z_far;
	res.m[0][0] = 1.0f / (tan_half_fov * aspect);
	res.m[0][1] = 0;
	res.m[0][2] = 0;
	res.m[0][3] = 0;
	res.m[1][0] = 0;
	res.m[1][1] = 1.0f / tan_half_fov;
	res.m[1][2] = 0;
	res.m[1][3] = 0;
	res.m[2][0] = 0;
	res.m[2][1] = 0;
	res.m[2][2] = (-z_near - z_far) / z_range;
	res.m[2][3] = 1;
	res.m[3][0] = 0;
	res.m[3][1] = 0;
	res.m[3][2] = 2.0f * z_far * z_near / z_range;
	res.m[3][3] = 1;
	return (res);
}

t_matrix multiply(t_matrix data1, t_matrix data2)
{
	t_matrix	res;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.m[i][j] = data1.m[i][0] * data2.m[0][j] + \
							data1.m[i][1] * data2.m[1][j] + \
							data1.m[i][2] * data2.m[2][j] + \
							data1.m[i][3] * data2.m[3][j];
			j++;
		}
		i++;
	}
	return (res);
}