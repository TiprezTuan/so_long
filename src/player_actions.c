/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:43:10 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/19 15:08:01 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include "mlx.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int	check_new_position(t_game *game, int px, int py)
{
	if (game->map.map[py][px] == WALL)
		return (0);
	if (game->map.map[py][px] == COLLECTIBLE)
	{
		game->nb_collectible_get++;
		return (2);
	}
	if (game->map.map[py][px] == EXIT)
		return (game->nb_collectible_get == game->nb_collectible_total);
	return (2);
}

void	update_player_position(t_game *game, int px, int py)
{
	int		old_x;
	int		old_y;
	int		status_func;
	char	*nb_moves;

	old_x = game->player.player_x;
	old_y = game->player.player_y;
	status_func = check_new_position(game, px, py);
	if (status_func)
	{
		game->player.player_x = px;
		game->player.player_y = py;
		game->map.map[py][px] = PLAYER;
		game->map.map[old_y][old_x] = FLOOR;
		game->player.nb_move++;
		nb_moves = ft_itoa(game->player.nb_move + 1);
		ft_putstr_fd("nb_moves = ", 1);
		ft_putendl_fd(nb_moves, 1);
		free(nb_moves);
	}
	if (status_func == 1)
		clean_exit(game);
}

int	player_actions(int key, t_game *game)
{
	int	px;
	int	py;

	px = game->player.player_x;
	py = game->player.player_y;
	if (key == W_UP || key == UP_ARROW)
		update_player_position(game, px, py - 1);
	else if (key == A_LEFT || key == LEFT_ARROW)
		update_player_position(game, px - 1, py);
	else if (key == S_DOWN || key == DOWN_ARROW)
		update_player_position(game, px, py + 1);
	else if (key == D_RIGHT || key == RIGHT_ARROW)
		update_player_position(game, px + 1, py);
	else if (key == ESC_BUTTON)
		clean_exit(game);
	else
		return (0);
	update_textures(game);
	return (1);
}
