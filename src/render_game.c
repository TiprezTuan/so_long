/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:21:25 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/19 15:06:30 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include "mlx.h"

static void	put_texture(t_game *game, void *texture, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, texture,
		x * game->map.tile_size, y * game->map.tile_size);
}

static void	set_textures(t_game *game, char loc, int loc_x, int loc_y)
{
	if (loc == WALL)
		put_texture(game, game->textures.wall, loc_x, loc_y);
	if (loc == FLOOR)
		put_texture(game, game->textures.floor, loc_x, loc_y);
	if (loc == COLLECTIBLE)
		put_texture(game, game->textures.collectible, loc_x, loc_y);
	if (loc == EXIT)
		put_texture(game, game->textures.exit, loc_x, loc_y);
	if (loc == PLAYER)
		put_texture(game, game->textures.player, loc_x, loc_y);
	if (loc == PORTAL)
		put_texture(game, game->textures.portal, loc_x, loc_y);
}

void	update_textures(t_game *game)
{
	int		i;
	int		j;
	char	*nb_moves;

	i = -1;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
			set_textures(game, game->map.map[i][j], j, i);
	}
	nb_moves = ft_itoa(game->player.nb_move);
	mlx_string_put(game->mlx, game->win, 30, 30, 0xFF0000, nb_moves);
	free(nb_moves);
}
