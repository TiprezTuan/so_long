/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:24:11 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/16 16:14:55 by ttiprez          ###   ########.fr       */
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
	int			map_height;
	int			map_width;
	char		**map;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;

	t_textures	textures;
	t_player	player;
	t_map		map;

	int			nb_collectible_total;
	int			nb_collectible_get;
}	t_game;

typedef struct s_pathfinder
{
	int	x;
	int y;
	int	nb_component_get;
	int	nb_component_total;
}	t_pathfinder;

#endif