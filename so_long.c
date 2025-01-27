/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 20:55:54 by bnafiai           #+#    #+#             */
/*   Updated: 2025/01/24 19:01:30 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(t_data *game)
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
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	put_images(t_data *game)
{
	int	img_width;
	int	img_height;

	game->wall_img = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &img_width, &img_height);
	game->knight_img = mlx_xpm_file_to_image(game->mlx,
			"textures/knight_1_.xpm", &img_width, &img_height);
	game->coin_img = mlx_xpm_file_to_image(game->mlx,
			"textures/coin.xpm", &img_width, &img_height);
	game->door_img = mlx_xpm_file_to_image(game->mlx,
			"textures/door.xpm", &img_width, &img_height);
	if (!game->wall_img || !game->coin_img
		|| !game->knight_img || !game->door_img)
	{
		cleanup_images(game);
		ft_printf("Error:\nloading pics\n");
		exit(1);
	}
}

int	initial_game(char *map_path, t_data *game)
{
	game->map = read_map(map_path, game);
	if (!game->map)
	{
		ft_printf("Error\nReading map\n");
		cleanup(game);
		return (1);
	}
	game->count_e = 0;
	game->count_p = 0;
	check_map(game);
	check_map2(game);
	find_player(game);
	count_coins(game);
	if (invalid_path(game))
	{
		cleanup(game);
		return (1);
	}
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "2D Game");
	put_images(game);
	render_map(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	game;
	int		fd;

	if (argc != 2 || !check_ext(argv[1], ".ber"))
	{
		ft_printf("Error\nIncorrect usage <map_file.ber>\n");
		return (1);
	}
	game.mlx = mlx_init();
	fd = open_map_file(argv[1]);
	if (fd < 0 || !valid_map_file(fd, &game, 0))
	{
		if (fd >= 0)
			close(fd);
		mlx_destroy_display(game.mlx);
		free(game.mlx);
		return (1);
	}
	initial_game(argv[1], &game);
	game.move_score = 0;
	game.coins_remaining = 0;
	mlx_hook(game.win, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.win, 17, 0L, handle_close, &game);
	mlx_loop(game.mlx);
	return (0);
}
