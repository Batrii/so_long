/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 20:49:12 by bnafiai           #+#    #+#             */
/*   Updated: 2025/01/24 17:28:14 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <mlx.h>
# include "get_next_line.h"
# include "ft_printf.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# define TILE_SIZE 20

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*wall_img;
	void	*knight_img;
	void	*coin_img;
	void	*door_img;
	int		coins_remaining;
	int		coin_count;
	char	**map;
	int		player_x;
	int		player_y;
	int		move_score;
	int		map_height;
	int		map_width;
	int		count_e;
	int		count_p;
	int		reachable_c;
	int		reachable_e;
}	t_data;
int		open_map_file(const char *file_name);
int		valid_map_file(int fd, t_data *game, int expected_lenght);
void	cleanup(t_data *game);
void	cleanup_images(t_data *game);
int		check_ext(char *str, char *ber);
void	check_map(t_data *game);
void	check_map2(t_data *game);
char	**read_map(char *filename, t_data *game);
int		rep_fun(t_data *game, void *i, int x, int y);
void	render_map(t_data *game);
void	count_coins(t_data *game);
void	flood_fill(char **map, int y, int x, t_data *game);
int		invalid_path(t_data *game);
char	*my_strchr2(const char *str, int c);
size_t	my_strlen2(const char *str);
char	*my_strdup3(char *str);
int		handle_key(int keycode, t_data *game);
int		handle_close(t_data *game);
void	free_map(char **map, int rows);
#endif
