#include "head.h"

double percent(int start, int end, int current)
{
    double placement;
    double distance;

    placement = current - start;
    distance = end - start;
    return ((distance == 0) ? 1.0 : (placement / distance));
}

int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int		get_color(t_color *color, t_line ln)
{
	double	percentage;
	int		r;
	int		g;
	int		b;
	int		ret;

	//if (color->start > color->end)
	//	ft_swap(&color->start, &color->end);
	if (color->start == color->end)
		return (color->end);
	percentage = ln.dx > ln.dy ? percent(ln.xs, ln.xe, ln.x) : percent(ln.ys, ln.ye, ln.y);
	// printf("percent = %f\n", percentage);
	//printf("%d %d\n", color->start, color->end);
	r = get_light((color->start >> 16) & 0xFF, (color->end >> 16) & 0xFF, percentage);
	g = get_light((color->start >> 8) & 0xFF, (color->end >> 8) & 0xFF, percentage);
	b = get_light(color->start & 0xFF, color->end & 0xFF, percentage);
	ret = (r << 16) | (g << 8) | b;
	// if (ret == 0x0)
	// 	ret++;
	// printf("ret color = %d curr = %d\n", ret, color->curr);
	return (ret);//(r << 16) | (g << 8) | b);
}