#include "../includes/scop.h"

t_vector init_vec(float x, float y, float z, float w)
{
	t_vector v;

	v.v[0] = x;
	v.v[1] = y;
	v.v[2] = z;
	v.v[3] = w;
	return v;
}