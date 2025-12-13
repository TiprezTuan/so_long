/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:02:43 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/13 15:59:01 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;
}	t_data;

void	clean_exit(t_data *data, int exit_status)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(exit_status);
}

int	deal_key(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == 65307)
	{
		clean_exit(data, EXIT_SUCCESS);
		exit (EXIT_SUCCESS);
	}
	printf("Key %d is pressed\n", key);
	return (0);
}

int main()
{
	t_data	data;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (EXIT_FAILURE);
	data.win = mlx_new_window(data.mlx, 800, 600, "so_long");

	mlx_pixel_put(data.mlx, data.win, 250, 250, 0xFF0000);
	mlx_string_put(data.mlx, data.win, 200, 200, 0xFFFF, "Hello World!");

	mlx_key_hook(data.win, deal_key, &data);
	mlx_loop(data.mlx);

	return (EXIT_FAILURE);
}
