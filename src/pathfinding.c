/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:39:10 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/17 16:30:21 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static void	count_nb_components(t_map *map, t_pathfinder *finder)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->map_height)
	{
		j = -1;
		while (++j < map->map_width)
			if (map->map[i][j] == COLLECTIBLE ||
				map->map[i][j] == EXIT)
				finder->nb_comp_total++;
	}
}

static void	set_finder_xy(t_map *map, t_pathfinder *finder)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->map_height)
	{
		j = 0;
		while (j < map->map_width)
		{
			if (map->map[i][j] == PLAYER)
			{
				finder->y = i;
				finder->x = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	browse_map(t_map *map, t_pathfinder *f, int nx, int ny)
{
	if (map->map[ny][nx] == EXIT ||
		map->map[ny][nx] == COLLECTIBLE)
		f->nb_comp_get++;
	if (map->map[ny][nx] == VISITED ||
		map->map[ny][nx] == WALL)
		return ;
	if (map->map[ny][nx] == EXIT)
	{
		map->map[ny][nx] = VISITED;
		return ;
	}
	map->map[ny][nx] = VISITED;
	browse_map(map, f, nx + 1, ny);
	browse_map(map, f, nx - 1, ny);
	browse_map(map, f, nx, ny + 1);
	browse_map(map, f, nx, ny - 1);
}

bool	pathfinder(t_map *map_copy, t_pathfinder *finder)
{
	count_nb_components(map_copy, finder);
	set_finder_xy(map_copy, finder);
	browse_map(map_copy, finder, finder->x, finder->y);
	free_map(map_copy);
	free(map_copy);
	return (finder->nb_comp_get == finder->nb_comp_total);
}
