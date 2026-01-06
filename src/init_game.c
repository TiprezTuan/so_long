/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:10:10 by ttiprez           #+#    #+#             */
/*   Updated: 2026/01/06 16:36:21 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

#include <stdlib.h>

static bool	init_textures(t_game *game)
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
	game->textures.portal = mlx_xpm_file_to_image(game->mlx,
			"./texture/portal.xpm", &w, &h);
	if (!game->textures.floor || !game->textures.exit
		|| !game->textures.collectible || !game->textures.player
		|| !game->textures.wall ||!game->textures.portal)
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
		clean_exit_err(game, "Error\nFailed to load images");
	game->win = mlx_new_window(game->mlx,
			game->map.map_width * game->map.tile_size,
			game->map.map_height * game->map.tile_size, "so_long");
	if (!game->win)
		clean_exit_err(game, "Error\nFailed to create window");
	set_player_position(game);
	set_portals_positions(game);
	set_nb_collectible(game);
}

void	init_game_value(t_game *game)
{
	game->map.map = NULL;
	game->mlx = NULL;
	game->win = NULL;
	game->textures.collectible = NULL;
	game->textures.floor = NULL;
	game->textures.exit = NULL;
	game->textures.player = NULL;
	game->textures.wall = NULL;
	game->textures.portal = NULL;
	game->nb_collectible_get = 0;
	game->nb_collectible_total = 0;
	game->player.nb_move = 0;
	game->portals.entry_x = 0;
	game->portals.entry_x = 0;
	game->portals.exit_x = 0;
	game->portals.exit_y = 0;
}
