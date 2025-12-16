/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:21:25 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/16 13:02:45 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

static void	put_texture(t_game *game, void *texture, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, texture, 
			x * game->map.tile_size, y * game->map.tile_size);
}

void	update_textures(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
		{
			if (game->map.map[i][j] == WALL)
				put_texture(game, game->textures.wall, i, j);
			if (game->map.map[i][j] == FLOOR)
				put_texture(game, game->textures.floor, i, j);
			if (game->map.map[i][j] == COLLECTIBLE)
				put_texture(game, game->textures.collectible, i, j);
			if (game->map.map[i][j] == EXIT)
				put_texture(game, game->textures.exit, i, j);
			if (game->map.map[i][j] == PLAYER)
				put_texture(game, game->textures.player, i, j);
		}
	}
}