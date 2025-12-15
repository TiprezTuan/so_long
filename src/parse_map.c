/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:18:50 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/15 14:48:28 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"
#include "libft.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static void	count_components(t_game *game, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == COLLECTIBLE)
			game->nb_collectible_total++;
		if (line[i] == PLAYER)
			game->nb_player++;
		if (line[i] == EXIT)
			game->nb_exit++;
	}	
}

static int	count_lines_map(t_game *game, char *pathname_map)
{
	int	fd;
	int	nb_lines;

	fd = open(pathname_map, O_RDONLY);
	if (fd < 0)
	{
		perror(pathname_map);
		exit(EXIT_FAILURE);
	}
	while (get_next_line(fd))
		nb_lines++;
	close(fd);
	if (nb_lines < 3)
		clean_exit_err(game, "Error\nInvalid map size.");
	return (nb_lines);
}

char	**parse_map(t_game *game, char *pathname_map)
{
	char	**map;
	char	*content_gnl;
	int		fd;
	int		i;

	map = malloc(sizeof(char *) * (count_lines_map(game, pathname_map) + 1));
	fd = open(pathname_map, O_RDONLY);
	if (fd < 0)
	{
		perror(pathname_map);
		free(map);
	}
	i = 0;
	content_gnl = get_next_line(fd);
	game->nb_collectible_total = 0;
	while (content_gnl)
	{
		map[i++] = content_gnl;
		count_components(game, content_gnl);
		content_gnl = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}