/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:18:50 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/19 15:14:39 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"
#include "libft.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static int	count_lines_map(t_game *game, char *pathname_map)
{
	int		fd;
	int		nb_lines;
	char	*content;

	fd = open(pathname_map, O_RDONLY);
	if (fd < 0)
	{
		perror(pathname_map);
		exit(EXIT_FAILURE);
	}
	nb_lines = 0;
	content = get_next_line(fd);
	while (content)
	{
		nb_lines++;
		free(content);
		content = get_next_line(fd);
	}
	close(fd);
	if (nb_lines < 3)
		clean_exit_err(game, "Error\nMinimum size 3x3\n");
	return (nb_lines);
}

void	set_player_position(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
		{
			if (game->map.map[i][j] == PLAYER)
			{
				game->player.player_x = j;
				game->player.player_y = i;
				return ;
			}
		}
	}
}

void	set_nb_collectible(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
			if (game->map.map[i][j] == COLLECTIBLE)
				game->nb_collectible_total++;
	}
}

void	set_portals_positions(t_game *game)
{
	int	i;
	int	j;
	int	portal_selected;

	portal_selected = 1;
	i = -1;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
		{
			if (game->map.map[i][j] == PORTAL && portal_selected == 1)
			{
				portal_selected++;
				game->portals.entry_y = i;
				game->portals.entry_x = j;
			}
			else if (game->map.map[i][j] == PORTAL && portal_selected == 2)
			{
				game->portals.exit_y = i;
				game->portals.exit_x = j;
			}
		}
	}
}

char	**parse_map(t_game *game, char *pathname_map)
{
	char	**map;
	char	*content_gnl;
	int		fd;
	int		i;

	game->map.map_height = count_lines_map(game, pathname_map);
	map = malloc(sizeof(char *) * (game->map.map_height + 1));
	fd = open(pathname_map, O_RDONLY);
	if (fd < 0)
	{
		perror(pathname_map);
		free(map);
	}
	i = 0;
	content_gnl = get_next_line(fd);
	game->map.map_width = ft_strlen(content_gnl) - 1;
	game->nb_collectible_total = 0;
	while (content_gnl)
	{
		map[i++] = content_gnl;
		content_gnl = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}
