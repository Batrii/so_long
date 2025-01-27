/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:56:12 by bnafiai           #+#    #+#             */
/*   Updated: 2025/01/22 20:44:26 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_coins(t_data *game)
{
	int	y;
	int	x;

	game->coin_count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				game->coin_count++;
			x++;
		}
		y++;
	}
}

char	**copy_map(char **map, int height)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		new_map[i] = my_strdup3(map[i]);
		if (!new_map[i])
		{
			free_map(new_map, i);
			return (NULL);
		}
		i++;
	}
	new_map[height] = NULL;
	return (new_map);
}

void	flood_fill(char **map, int y, int x, t_data *game)
{
	if (y < 0 || x < 0 || y >= game->map_height || x >= game->map_width)
		return ;
	if (map[y][x] == '1' || map[y][x] == '*')
		return ;
	if (map[y][x] == 'C')
		game->reachable_c++;
	if (map[y][x] == 'E')
		game->reachable_e++;
	map[y][x] = '*';
	flood_fill(map, y + 1, x, game);
	flood_fill(map, y - 1, x, game);
	flood_fill(map, y, x + 1, game);
	flood_fill(map, y, x - 1, game);
}

int	invalid_path(t_data *game)
{
	char	**map_copy;

	map_copy = copy_map(game->map, game->map_height);
	if (!map_copy)
		return (1);
	game->reachable_c = 0;
	game->reachable_e = 0;
	flood_fill(map_copy, game->player_y, game->player_x, game);
	if (game->reachable_c != game->coin_count
		|| game->reachable_e != game->count_e)
	{
		ft_printf("Error:\nInvalid path: can't reach all coins or the exit\n");
		free_map(map_copy, game->map_height);
		return (1);
	}
	free_map(map_copy, game->map_height);
	return (0);
}

void	cleanup_images(t_data *game)
{
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->coin_img)
		mlx_destroy_image(game->mlx, game->coin_img);
	if (game->knight_img)
		mlx_destroy_image(game->mlx, game->knight_img);
	if (game->door_img)
		mlx_destroy_image(game->mlx, game->door_img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->map)
		free_map(game->map, game->map_height);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
