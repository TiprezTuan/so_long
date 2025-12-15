/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:32:41 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/15 14:43:31 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include "mlx.h"

#include <stdlib.h>

static void	destroy_all_images(t_game *game)
{
	if (game->textures.floor)
		mlx_destroy_image(game->mlx, game->textures.floor);
	if (game->textures.exit)
		mlx_destroy_image(game->mlx, game->textures.exit);
	if (game->textures.collectible)
		mlx_destroy_image(game->mlx, game->textures.collectible);
	if (game->textures.player)
		mlx_destroy_image(game->mlx, game->textures.player);
	if (game->textures.wall)
		mlx_destroy_image(game->mlx, game->textures.wall);
}

static void	free_map(t_game *game)
{
	int	i;

	i = -1;
	while (game->map.map[++i])
		free(game->map.map[i]);
	free(game->map.map);
}

void	clean_exit_err(t_game *game, char *msg)
{
	if (game->map.map)
		free_map(game);
	//destroy_all_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	//ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}