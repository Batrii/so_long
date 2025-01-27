/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:53:08 by bnafiai           #+#    #+#             */
/*   Updated: 2025/01/17 14:26:36 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_movement(int keycode, t_data *game)
{
	if (keycode == 119)
	{
		if (game->player_y > 0
			&& game->map[game->player_y - 1][game->player_x] != '1')
			game->player_y--;
	}
	else if (keycode == 97)
	{
		if (game->player_x > 0
			&& game->map[game->player_y][game->player_x - 1] != '1')
			game->player_x--;
	}
	else if (keycode == 115)
	{
		if (game->player_y < game->map_height - 1
			&& game->map[game->player_y + 1][game->player_x] != '1')
			game->player_y++;
	}
	else if (keycode == 100)
	{
		if (game->player_x < game->map_width - 1
			&& game->map[game->player_y][game->player_x + 1] != '1')
			game->player_x++;
	}
}

int	handle_close(t_data *game)
{
	free_map(game->map, game->map_height);
	mlx_destroy_image(game->mlx, game->wall_img);
	mlx_destroy_image(game->mlx, game->coin_img);
	mlx_destroy_image(game->mlx, game->knight_img);
	mlx_destroy_image(game->mlx, game->door_img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

void	update_game(t_data *game, int prev_x, int prev_y)
{
	if (prev_x != game->player_x || prev_y != game->player_y)
	{
		game->move_score++;
		mlx_clear_window(game->mlx, game->win);
		render_map(game);
		mlx_put_image_to_window(game->mlx, game->win,
			game->knight_img, game->player_x * TILE_SIZE,
			game->player_y * TILE_SIZE);
	}
	ft_printf("Move score: %d\n", game->move_score);
}

int	handle_key(int keycode, t_data *game)
{
	int	prev_x ;
	int	prev_y ;

	prev_x = game->player_x;
	prev_y = game->player_y;
	if (keycode == 65307)
		return (handle_close(game));
	handle_movement(keycode, game);
	if (game->map[game->player_y][game->player_x] == 'C')
	{
		game->map[game->player_y][game->player_x] = '0';
		game->coins_remaining++;
	}
	if (game->map[game->player_y][game->player_x] == 'E'
		&& game->coins_remaining == game->coin_count)
		return (handle_close(game));
	update_game(game, prev_x, prev_y);
	return (0);
}
