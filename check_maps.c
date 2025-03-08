/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:29:48 by bnafiai           #+#    #+#             */
/*   Updated: 2025/03/08 17:12:05 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
 
void	check_map(t_data *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
				game->count_p++;
			if (game->map[y][x] == 'E')
				game->count_e++;
			x++;
		}
		y++;
	}
	if (game->count_e != 1 || game->count_p != 1)
	{
		if (game->count_p != 1)
			ft_printf("Error\nJust one player please\n");
		if (game->count_e != 1)
			ft_printf("Error\nOne exit please\n");
		cleanup(game);
	}
}

void	check_map2(t_data *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map_width)
	{
		if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1')
		{
			ft_printf("Error\nMap not surrounded by walls\n");
			cleanup(game);
		}
		x++;
	}
	y = 0;
	while (y < game->map_height)
	{
		if (game->map[y][0] != '1' || game->map[y][game->map_width - 1] != '1')
		{
			ft_printf("Error\nMap not surrounded by walls\n");
			cleanup(game);
		}
		y++;
	}
}

static int	read_map_lines(int fd, char **map, int map_height)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line && i < map_height)
	{
		map[i] = line;
		if (!map[i])
		{
			free(line);
			free_map(map, i);
			close(fd);
			return (0);
		}
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (1);
}

char	**read_map(char *filename, t_data *game)
{
	int		fd;
	char	**map;

	fd = open_map_file(filename);
	map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	if (!read_map_lines(fd, map, game->map_height))
	{
		free(map);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (map);
}

void	render_map(t_data *game)
{
	int	x;
	int	y;

	y = 0;
	if (!game || !game->mlx || !game->win
		|| !game->wall_img || !game->knight_img || !game->coin_img)
		return ;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				rep_fun(game, game->wall_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'C')
				rep_fun(game, game->coin_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == 'E' &&
				game->coins_remaining == game->coin_count)
				rep_fun(game, game->door_img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	rep_fun(game, game->knight_img,
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}
