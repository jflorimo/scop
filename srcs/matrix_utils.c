#include "../includes/scop.h"

t_matrix init_matrix_translation(void)
{
	float tab[4][4] ={
		{1, 0, 0, 10},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	}
	t_matrix m;
	m.m = tab;
	return m;
}