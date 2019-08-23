
#ifndef	FDF_H
# define FDF_H
#define WIN_X 500
#define WIN_Y 500

typedef struct		s_bsh
{
	int dx;
	int vx;
	int dy;
	int vy;
	int dir;
	int tmp;
}			t_bsh;

typedef struct		s_coord
{
	int x;
	int y;
	int z;
}			t_coord;

typedef struct		s_mlx
{
	void		*ptr;
	void		*win;
	void		*img;
	t_coord		**grid;
	int		*lengths;
}			t_mlx;

t_coord			op(t_coord i, char c, t_coord j);
t_mlx			init_mlx(void);
int			deal_key(int key, t_mlx *mlx_infos);
void			ft_bresenham(t_coord start, t_coord dest, t_mlx *mlx_infos);
void			applyvec(t_coord ***grid, t_coord vec, int *lengths);
void			print_grid(t_coord **grid, int *lengths, t_mlx mlx_infos);

#endif
