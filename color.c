#include "head.h"

int		get_color(t_color color, int axis, t_coor cr1, t_coor cr2)
{
	double	persentage;
	int		r;
	int		g;
	int		b;

	if (color.curr == color.end)
		return (color.end);
	persentage = axis ? persent(cr1.x, cr2.x, color.curr) : persent(cr1.y, cr2.y, color.curr);
}