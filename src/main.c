/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 09:54:24 by ttiprez           #+#    #+#             */
/*   Updated: 2026/01/06 16:36:37 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include "mlx.h"

#include <stdlib.h>

static void	check_argc(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putendl_fd("Error\n2 arguments needed", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(&av[1][ft_strlen(av[1]) - 4], ".ber") != 0)
	{
		ft_putendl_fd("Error\nMaps need .ber extension", 2);
		exit(EXIT_FAILURE);
	}
}

static t_map	*copy_map(t_map map)
{
	t_map	*map_copied;
	int		i;

	map_copied = malloc(sizeof(t_map));
	if (!map_copied)
		return (NULL);
	map_copied->map_height = map.map_height;
	map_copied->map_width = map.map_width;
	map_copied->map = malloc(sizeof(char *) * (map.map_height + 1));
	if (!map_copied->map)
		return (free(map_copied), NULL);
	i = 0;
	while (i < map.map_height)
	{
		map_copied->map[i] = ft_strdup(map.map[i]);
		if (!map_copied->map[i])
			return (free_map(map_copied), free(map_copied), NULL);
		i++;
	}
	map_copied->map[i] = NULL;
	return (map_copied);
}

static bool	check_map_values(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] && map[i][j + 1])
			if (!(map[i][j] == EXIT || map[i][j] == WALL || map[i][j] == PORTAL
				|| map[i][j] == PLAYER || map[i][j] == COLLECTIBLE ||
				map[i][j] == FLOOR))
				return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_game	game;

	check_argc(ac, av);
	init_game_value(&game);
	game.map.map = parse_map(&game, av[1]);
	if (!check_map_values(game.map.map))
	{
		ft_putendl_fd("Error\nThe map contains invalid values.", 2);
		clean_exit(&game);
	}
	if (!check_map_integrity(game.map.map, game.map.map_width))
		clean_exit(&game);
	if (!pathfinder(copy_map(game.map), &(t_pathfinder){0, 0, 0, 0}))
		clean_exit_err(&game, "Error\nNo valid path in the map");
	init_game(&game);
	update_textures(&game);
	mlx_hook(game.win, 17, 0, clean_exit, &game);
	mlx_hook(game.win, 02, (1L << 0), player_actions, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
