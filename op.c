#include "fdf.h"

static t_coord	subcoord(t_coord i, t_coord j)
{
	t_coord sub;

	sub.x = (i.x - j.x);
	sub.y = (i.y - j.y);
	return (sub);

}

static t_coord	addcoord(t_coord i, t_coord j)
{
	t_coord sum;

	sum.x = (i.x + j.x);
	sum.y = (i.y + j.y);
	return (sum);
}

t_coord	op(t_coord i, char c, t_coord j)
{
	t_coord new;

	if (c == '-')
		return (new = subcoord(i, j));
	else
		return (new = addcoord(i, j));
}
