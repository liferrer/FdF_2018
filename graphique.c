#include "mlx.h"
#include "libft/libft.h"
#include "fdf.h"

void	ft_zoom(t_mlx *mlx_infos)
{
	t_coord	**tmp;
	int	i;
	int	j;

	tmp = mlx_infos->grid;
	i = 0;
	j = 0;
	while (tmp[i])
	{
		while (j < mlx_infos->lengths[i])
		{
			(tmp[i][j]).x += 1 * i;
			(tmp[i][j]).y += 1 * j;
			j++;
		}
		j = 0;
		i++;
	}
}

void	putpixel(t_mlx *mlx_infos, t_coord start)
{
	mlx_pixel_put(mlx_infos->ptr, mlx_infos->win, start.x, start.y, 0x1EE110);
}

void	ft_bresenham(t_coord start, t_coord dest, t_mlx *mlx_infos)
{
	t_bsh bsh;

	bsh.dx = abs(dest.x - start.x);
	bsh.vx = (start.x<dest.x ? 1 : -1);
	bsh.dy = abs(dest.y - start.y);
	bsh.vy = (start.y<dest.y ? 1 : -1);
	bsh.dir = (bsh.dx>bsh.dy ? bsh.dx : -bsh.dy) / 2;
	while (start.x != dest.x || start.y != dest.y)
	{
		putpixel(mlx_infos, start);
		bsh.tmp = bsh.dir;
		if (bsh.tmp > -bsh.dx)
		{
			bsh.dir -= bsh.dy;
			start.x += bsh.vx;
		}
		if (bsh.tmp < bsh.dy)
		{
			bsh.dir += bsh.dx;
			start.y += bsh.vy;

		}
	}
	putpixel(mlx_infos, start);
}

int	deal_key(int key, t_mlx *mlx_infos)
{
	int		j;
	int		i;
	t_coord		vec;

	i = -1;
	j = 0;
	if (key == 53)
	{
		mlx_destroy_window(mlx_infos->ptr, mlx_infos->win);
		exit(0);
	}
	ft_putnbr((mlx_infos->lengths)[0]);
	ft_putnbr((mlx_infos->grid)[0][0].x);
	if (key == 123)
	{
		vec.x = -1;
		vec.y = 0;
		applyvec(&(mlx_infos->grid), vec, mlx_infos->lengths);
		mlx_clear_window(mlx_infos->ptr, mlx_infos->win);
		print_grid(mlx_infos->grid, mlx_infos->lengths, *mlx_infos);
	}
	
	if (key == 124)
	{
		vec.x = 1;
		vec.y = 0;
		applyvec(&(mlx_infos->grid), vec, mlx_infos->lengths);
		mlx_clear_window(mlx_infos->ptr, mlx_infos->win);
		print_grid(mlx_infos->grid, mlx_infos->lengths, *mlx_infos);
	}
	
	if (key == 125)
	{
		vec.x = 0;
		vec.y = 1;
		applyvec(&(mlx_infos->grid), vec, mlx_infos->lengths);
		mlx_clear_window(mlx_infos->ptr, mlx_infos->win);
		print_grid(mlx_infos->grid, mlx_infos->lengths, *mlx_infos);
	}
	
	if (key == 126)
	{
		vec.x = 0;
		vec.y = -1;
		applyvec(&(mlx_infos->grid), vec, mlx_infos->lengths);
		mlx_clear_window(mlx_infos->ptr, mlx_infos->win);
		print_grid(mlx_infos->grid, mlx_infos->lengths, *mlx_infos);
	}

	if (key == 24)
	{
		ft_zoom(mlx_infos);
		mlx_clear_window(mlx_infos->ptr, mlx_infos->win);
		print_grid(mlx_infos->grid, mlx_infos->lengths, *mlx_infos);
	}	
	return (0);
}

t_mlx	init_mlx(void)
{
	t_mlx	mlx_infos;
	void	*mlx_ptr;
	void	*mlx_win;

	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, 500, 500, "titre");
	mlx_infos.ptr = mlx_ptr;
	mlx_infos.win = mlx_win;

	return (mlx_infos);
}
