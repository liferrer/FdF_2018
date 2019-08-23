#include "libft/get_next_line.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"
#include "fdf.h"
#include "mlx.h"
#include <math.h>


void	applyvec(t_coord ***grid, t_coord vec, int *lenghts)
{
	int i;
	int j;
	t_coord **tmp;

	tmp = *grid;
	i = 0;
	j = -1;
	while (tmp[i])
	{
		while (++j < lenghts[i])
		{
			(tmp[i][j]).x += vec.x;
			(tmp[i][j]).y += vec.y;
		}
		j = -1;
		i++;
	}
}
void	print_grid(t_coord **grid, int *lengths, t_mlx mlx_infos)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(grid[i])
	{
		while(j + 1 < lengths[i])
		{
			ft_bresenham(grid[i][j], grid[i][j + 1], &mlx_infos);
			j++;
			
		}
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
	while (grid[i + 1])
	{
		while(j < lengths[i] && j < lengths[i + 1])
		{
			ft_bresenham(grid[i][j], grid[i + 1][j], &mlx_infos);
			j++;
		}
		j = 0;
		i++;
	}
}

void	get_isoview(t_coord ***grid, int *lengths)
{
	int i;
	int j;
	t_coord **tmp;

	tmp = *grid;
	i = 0;
	j = -1;
	while (tmp[i])
	{
		while (++j < lengths[i])
		{
			(tmp[i][j]).x = (sqrt(2.0) / 2.0) * ((tmp[i][j]).x - (tmp[i][j]).y);
			(tmp[i][j]).y = (sqrt(2.0 / 3.0)) * (tmp[i][j]).z - (1.0 / sqrt(6.0)) * ((tmp[i][j]).x + (tmp[i][j]).y);
		//	printf("x: %d | y: %d\n", (tmp[i][j]).x, (tmp[i][j]).y);
		}
		j = -1;
		i++;
	}
}

t_coord	getcentervec(int map_x, int map_y, t_coord **grid)
{
	t_coord centerstart;
	t_coord centerdest;
	t_coord ret;
	
	centerstart = grid[map_x / 2][map_y / 2];
	centerdest.x = (WIN_X / 2);
	centerdest.y = (WIN_Y / 2);
	
	ret = op(centerdest, '-', centerstart);
	printf("Vecteur mM : (x:%d ; y:%d)\n", ret.x, ret.y);

	return (ret);
}

int ft_max(int *array, int array_length)
{
	int i;
	int ret;

	i = -1;
	while(++i < array_length)
	{
		if (i == 0 || array[i] > ret)
			ret = array[i];
	}
	return (ret);
}

t_coord	**parse_map(char **tab, int nb_line, t_mlx *mlx_infos)
{
	char	**tmp;
	t_coord	**grid;
	t_coord vec;
	int	*lengths;
	int	i;
	int	j;
	int	k;
	
	int deltaX;
	int deltaY;

	deltaX = WIN_X / 30;
	deltaY = WIN_Y / 30;

	i = 0;
	j = -1;
	k = 0;
	
	grid = (t_coord**)malloc(sizeof(t_coord*) * (nb_line + 1));
	grid[nb_line] = NULL;
	if (!(lengths = (int*)malloc(sizeof(int) * (nb_line))))
		return (0);
	while (tab[i] != NULL)
	{
		tmp = ft_strsplit(tab[i], " \t");
		while (tmp[k])
			k++;
		lengths[i] = k;
		grid[i] = (t_coord*)malloc(sizeof(t_coord) * (k));
		k = 0;
		while (tmp[++j])
		{
			if (!(ft_isstrdigit(tmp[j])))
				return (0);
			grid[i][j].z = ft_atoi(tmp[j]);
			grid[i][j].x = i + i*deltaX;
			grid[i][j].y = j + j*deltaY;
		}
		j = -1;;
	i++;
	}
	
	get_isoview(&grid, lengths);
	vec = getcentervec(nb_line, ft_max(lengths, nb_line), grid);
	applyvec(&grid, vec, lengths);
	mlx_infos->grid = grid;
	mlx_infos->lengths = lengths;
	print_grid(grid, lengths, *mlx_infos);
	return (grid);
}

void	ft_fdf(char *filename, t_mlx *mlx_infos)
{
	int	i;
	int	fd;
	char	**tab;
	int	ret;
	char	*line;
	char	*tmp;
	
	fd = open(filename, O_RDONLY);
	tmp = "";
	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		i++;
		line = ft_strjoin(line, "\n");
		tmp = ft_strjoin(tmp, line);
	}
	tab = ft_strsplit(tmp, "\n");
	parse_map(tab, i, mlx_infos);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx_infos;

	if (argc < 2) {
		printf("Enculé, t'as oublié la map !!!");	
		return (0);
	}
	mlx_infos = init_mlx();
	mlx_infos->img = mlx_new_image(mlx_infos->ptr, mlx_infos->win, WIN_X, WIN_Y);
	ft_fdf(argv[1], &mlx_infos);
	mlx_key_hook(mlx_infos.win, deal_key, (void *)&mlx_infos);
	mlx_loop(mlx_infos.ptr);
	return (0);

}
