/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:55:29 by bnafiai           #+#    #+#             */
/*   Updated: 2025/01/24 18:53:27 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

void	cleanup(t_data *game)
{
	free_map(game->map, game->map_height);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

int	open_map_file(const char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nFailed to open file: %s\n", file_name);
		return (-1);
	}
	return (fd);
}

static int	valid_line(const char *line, int expected_lenght)
{
	int	curr_lenght;
	int	i;

	curr_lenght = my_strlen2(line);
	if (curr_lenght != expected_lenght)
	{
		ft_printf("Error\nIncorrect map lenght\n");
		return (0);
	}
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!my_strchr2("01PEC", line[i]))
		{
			ft_printf("Error\nInvalid character\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	valid_map_file(int fd, t_data *game, int expected_lenght)
{
	char	*line;

	game->map_height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (game->map_height == 0)
			expected_lenght = my_strlen2(line);
		if (!valid_line(line, expected_lenght))
		{
			free(line);
			return (0);
		}
		game->map_height++;
		free(line);
		line = get_next_line(fd);
	}
	if (game->map_height == 0)
	{
		ft_printf("Error\nMap empty\n");
		return (0);
	}
	game->map_width = expected_lenght - 1;
	close(fd);
	return (1);
}
