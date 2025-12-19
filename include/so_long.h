/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 09:54:45 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/19 14:41:41 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "struct.h"

# include <stdbool.h>

# define COLLECTIBLE	'C'
# define PLAYER			'P'
# define PORTAL			'X'
# define EXIT			'E'
# define WALL			'1'
# define FLOOR			'0'
# define VISITED		'V'
# define W_UP			119
# define A_LEFT			97
# define S_DOWN			115
# define D_RIGHT		100
# define UP_ARROW		65362
# define LEFT_ARROW		65361
# define DOWN_ARROW		65364
# define RIGHT_ARROW	65363
# define ESC_BUTTON		65307

/*		parse_map.c		*/
void	set_player_position(t_game *game);
void	set_nb_collectible(t_game *game);
void	set_portals_positions(t_game *game);
char	**parse_map(t_game *game, char *pathname_map);

/*		check_map_integrity.c		*/
bool	check_map_integrity(char **map);

/*		error_management.c		*/
void	free_map(t_map *map);
void	clean_exit_err(t_game *game, char *msg);
int		clean_exit(t_game *game);

/*		render_game.c		*/
void	update_textures(t_game *game);

/*		player_actions.c	*/
int		player_actions(int key, t_game *game);

/*		pathfinding.c	   */
bool	pathfinder(t_map *map_copy, t_pathfinder *finder);

/*		init_game.c		 */
void	init_game(t_game *game);
void	init_game_value(t_game *game);

#endif