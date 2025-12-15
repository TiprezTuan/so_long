/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:24:11 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/15 14:44:08 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_textures
{
	void	*wall;
	void	*floor;
	void	*collectible;
	void	*player;
	void	*exit;
}	t_textures;

typedef struct s_player
{
	int			player_x;
	int			player_y;
	int			nb_move;
}	t_player;

typedef struct s_map
{
	int			tile_size;
	int			screen_height;
	int			screen_width;
	char		**map;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;

	t_textures	textures;
	t_player	player;
	t_map		map;

	int			nb_exit;
	int			nb_player;
	int			nb_collectible_total;
	int			nb_collectible_get;
}	t_game;

#endif