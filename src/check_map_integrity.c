/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_integrity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:59:20 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/15 14:39:51 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

#include <unistd.h>
#include <fcntl.h>

bool	check_map_integrity(char **map)
{
	int	line_size;
	int	i;

	i = 0;
	line_size = ft_strlen(map[i]);
	while (map[++i])
	{
		if (ft_strlen(map[i]) != line_size)
		{
			ft_putendl_fd("Error\n", 2);
			ft_putstr_fd("2 lines with differents size. ", 2);
			ft_putendl_fd("Map must be rectangle.", 2);
			return (false);
		}
	}
	return (true);
}
