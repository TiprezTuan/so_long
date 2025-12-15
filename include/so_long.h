/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 09:54:45 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/15 14:37:54 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "struct.h"

# include <stdbool.h>

# define COLLECTIBLE	'c'
# define PLAYER			'P'
# define EXIT			'E'
# define WALL			'1'
# define FLOOR			'0'

/*		parse_map.c		*/
char	**parse_map(t_game *game, char *pathname_map);
bool	check_map_integrity(char **map);

/*		error_management.c		*/
void	clean_exit_err(t_game *game, char *msg);

#endif