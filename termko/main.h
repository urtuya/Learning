/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 05:28:11 by ydavis            #+#    #+#             */
/*   Updated: 2019/04/20 14:58:11 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "libft/libft.h"
# include "mlx.h"
# include <math.h>

typedef struct	s_line
{
	int		x0;
	int		y0;
	int		x;
	int		y;
	float	altjx;
	float	altjy;
	float	div;
	int		start_col;
	int		end_col;
}				t_line;
typedef struct	s_lines
{
	t_line			*line;
	struct s_lines	*next;
}				t_lines;
typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
}				t_mlx;
typedef struct	s_points
{
	double	**array;
	int		width;
	int		length;
	double	min_height;
	double	max_height;
	double	minmax;
	double	coef;
	double	**arrx;
	double	**arry;
	double	**arrz;
}				t_points;
typedef struct	s_fdf
{
	t_mlx		*mlx;
	t_points	*points;
	t_lines		*linesx;
	t_lines		*linesy;
	double		angle;
	int			mouse;
	int			clickx;
	int			clicky;
	int			offx;
	int			offy;
	int			max_col;
	int			min_col;
	int			rotate;
	int			project;
	int			help;
	int			shift;
	int			isfirst;
	int			normal;
}				t_fdf;
double			**create_rot_x(double angle);
double			**create_rot_z(double angle);
double			percent(int start, int end, int current);
t_fdf			*fdf_malloc(int ac, char **av);
void			iso_line_x(t_fdf *fdf, int i, int j, t_line *ret);
void			pers_line_x(t_fdf *fdf, int i, int j, t_line *ret);
void			lines_x(t_fdf *fdf, int i, int j, t_line *line);
void			iso_line_y(t_fdf *fdf, int i, int j, t_line *line);
void			pers_line_y(t_fdf *fdf, int i, int j, t_line *ret);
void			lines_y(t_fdf *fdf, int i, int j, t_line *line);
void			recreate_picture(t_fdf *fdf, int flag);
void			getlines_x(t_fdf *fdf);
void			getlines_y(t_fdf *fdf);
void			putlines_x(t_fdf *fdf);
void			putlines_y(t_fdf *fdf);
void			init_constants(t_fdf *fdf);
void			points_parse(t_fdf *fdf);
void			map_arr(t_points *str);
void			get_mlx(t_fdf *fdf);
void			scroll_up(t_fdf *fdf);
void			scroll_down(t_fdf *fdf);
void			ft_error(char *str);
void			rotate_x(t_fdf *fdf, double angle);
void			rotate_z(t_fdf *fdf, double angle);
void			normalize_arr(t_points *str);
void			delete_xyz(t_fdf *fdf);
void			free_tmp(char **tmp);
void			free_lines(t_lines *lines);
void			check_malloc(void *addr);
void			mult_matrix(t_fdf *fdf, double **mat2, int w);
void			normalize_y(t_fdf *fdf);
void			free_matrix(double **mat);
void			mouse_helper(int x, int y, t_fdf *fdf);
void			fill_arr(t_fdf *fdf, char **lines);
void			get_points(t_fdf *fdf, char *file, int fd);
void			fill_str(char *file, char *str);
int				get_length(t_fdf *fdf, int fd);
int				hex_atoi(char *str);
int				loop_hook(t_fdf *fdf);
int				key_hook(int keycode, t_fdf *fdf);
int				get_light(int start, int end, double percentage);
int				get_greater_col(t_fdf *fdf, int i, int j, char axis);
int				get_lesser_col(t_fdf *fdf, int i, int j, char axis);
int				choose_color(t_line *line, int current, char axis);
int				color_returner(t_fdf *fdf, double z);
int				mouse_press(int button, int x, int y, t_fdf *param);
int				mouse_release(int button, int x, int y, t_fdf *param);
int				mouse_move(int x, int y, t_fdf *param);
int				ft_count(char **line);
int				mouse_move(int x, int y, t_fdf *param);
#endif
