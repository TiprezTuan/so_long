/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_integrity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:59:20 by ttiprez           #+#    #+#             */
/*   Updated: 2026/01/05 11:47:32 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

#include <stdio.h>

static bool	is_enclosed_by_wall(char **map, int map_width)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		if (i == 0 || !map[i + 1])
		{
			j = -1;
			while (map[i][++j] && map[i][j + 1])
				if (map[i][j] != WALL)
					return (false);
		}
		else
		{
			j = -1;
			if (map[i][0] != WALL)
				return (false);
			if (map[i][map_width - 1] != WALL)
				return (false);
		}
	}
	return (true);
}

static bool	is_rectangle(char **map)
{
	int	line_size;
	int	i;

	i = 0;
	line_size = ft_strlen(map[i]);
	while (map[++i])
		if (ft_strlen(map[i]) != line_size)
			return (false);
	return (true);
}

static bool	have_valid_components(char **map)
{
	int	i;
	int	j;
	int	nb_exit;
	int	nb_collectible;
	int	nb_player;

	i = -1;
	nb_exit = 0;
	nb_collectible = 0;
	nb_player = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == COLLECTIBLE)
				nb_collectible++;
			if (map[i][j] == EXIT)
				nb_exit++;
			if (map[i][j] == PLAYER)
				nb_player++;
		}
	}
	return (nb_exit == 1 && nb_player == 1 && nb_collectible > 0);
}

static bool	have_valid_numbers_of_portals(char **map)
{
	int	nb_portals;
	int	i;
	int	j;

	nb_portals = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == PORTAL)
				nb_portals++;
	}
	return (nb_portals == 0 || nb_portals == 2);
}

bool	check_map_integrity(char **map, int map_width)
{
	if (!is_enclosed_by_wall(map, map_width))
	{
		ft_putendl_fd("Error", 2);
		return (ft_putendl_fd("The map must be enclosed by wall.", 2), false);
	}
	if (!is_rectangle(map))
	{
		ft_putstr_fd("Error\n2 lines with differents size. ", 2);
		return (ft_putendl_fd("The map must be a rectangle.", 2), false);
	}
	if (!have_valid_components(map))
	{
		ft_putstr_fd("Error\nThe map must contain 1 exit, 1 starting ", 2);
		ft_putendl_fd("position, at least 1 collectible and 0 or 2 portals", 2);
		return (false);
	}
	if (!have_valid_numbers_of_portals(map))
	{
		ft_putendl_fd("Error\nThe map must contain 0 or 2 portals.", 2);
		return (false);
	}
	return (true);
}
