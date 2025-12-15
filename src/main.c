/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 09:54:24 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/15 14:47:16 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include "mlx.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool	init_textures(t_game *game)
{
	int	w;
	int	h;

	game->textures.floor = mlx_xpm_file_to_image(game->mlx,
			"./texture/floor.xpm", &w, &h);
	game->textures.exit = mlx_xpm_file_to_image(game->mlx,
			"./texture/exit.xpm", &w, &h);
	game->textures.collectible = mlx_xpm_file_to_image(game->mlx,
			"./texture/collectible.xpm", &w, &h);
	game->textures.player = mlx_xpm_file_to_image(game->mlx,
			"./texture/player.xpm", &w, &h);
	game->textures.wall = mlx_xpm_file_to_image(game->mlx,
			"./texture/wall.xpm", &w, &h);
	if (!game->textures.floor || !game->textures.exit
		|| !game->textures.collectible
		|| !game->textures.player || !game->textures.wall)
		return (false);
	game->map.tile_size = w;
	return (true);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit (EXIT_FAILURE);
	if (!init_textures(game))
		clean_exit_err(game, "Failed to load images");
	game->win = mlx_new_window(game->mlx, 800, 600, "so_long");
	if (!game->win)
		clean_exit_err(game, "Failed to create window");
}

void	check_argc(int ac, char **av)
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

void	init_game_value(t_game *game)
{
	game->nb_collectible_get = 0;
	game->nb_collectible_total = 0;
	game->nb_exit = 0;
	game->nb_player = 0;
}

int	main(int ac, char **av)
{
	t_game	game;

	check_argc(ac, av);
	init_game_value(&game);
	game.map.map = parse_map(&game, av[1]);
	if (!check_map_integrity(game.map.map))
		clean_exit_err(&game, NULL);
	init_game(&game);
	mlx_loop(game.mlx);
	return (EXIT_FAILURE);
}
