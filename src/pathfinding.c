/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:39:10 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/16 16:53:30 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static void	init_finder(char **map, t_pathfinder *finder)
{
	int	y;
	int	x;

	finder->x = 0;
	finder->nb_component_total = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == COLLECTIBLE ||
				map[y][x] == PLAYER || map[y][x] == EXIT)
			{
				if (finder->x == 0)
				{
					finder->x = x;
					finder->y = y;
					finder->nb_component_get = 1;
				}
				finder->nb_component_total++;
			}
		}
	}
}

static bool	find_way(t_map *map, t_pathfinder *finder)
{
	while (finder->y < map->map_height)
	{
		while (finder->x < map->map_width)
		{
			if (map->map[finder->y][finder->x] == WALL) // On arrive a un mur
			{
				// On conserve finder.x et finder.y
				// On lance une fonction qui a une copie de finder.x et finder.y
				// On par en profondeur
				// 		Si on a reussi a remonter a 
			}
			else
				finder->x++;
		}
		finder_y++;
	}
}

bool	pathfinder(t_map *map)
{
	t_pathfinder	finder;

	init_finder(map->map, &finder);
	return (find_way(map->map, &finder)); // Mettre message d'erreur
}



//chatgpt
#include <stdio.h>

#define HAUTEUR 10
#define LARGEUR 10

char g_map[HAUTEUR][LARGEUR + 1] = {
    "1111111111",
    "1000110001",
    "100P000001",
    "1011111011",
    "1010001001",
    "1011111C01",
    "1000000001",
    "1000000001",
    "10000000E1",
    "1111111111"
};

typedef struct s_case
{
    int x;
    int y;
}   t_case;

void trouver_depart_arrivee(int *dep_x, int *dep_y,
                            int *arr_x, int *arr_y)
{
    int ligne;
    int colonne;

    ligne = 0;
    while (ligne < HAUTEUR)
    {
        colonne = 0;
        while (colonne < LARGEUR)
        {
            if (g_map[ligne][colonne] == 'P')
            {
                *dep_x = colonne;
                *dep_y = ligne;
            }
            if (g_map[ligne][colonne] == 'E')
            {
                *arr_x = colonne;
                *arr_y = ligne;
            }
            colonne++;
        }
        ligne++;
    }
}

int est_atteignable(int dep_x, int dep_y, int arr_x, int arr_y)
{
    int visite[HAUTEUR][LARGEUR] = {0};
    t_case file[HAUTEUR * LARGEUR];
    int debut = 0;
    int fin = 0;
    int dir[4][2] = {{0,-1},{0,1},{-1,0},{1,0}};

    file[fin++] = (t_case){dep_x, dep_y};
    visite[dep_y][dep_x] = 1;
    while (debut < fin)
    {
        t_case cur = file[debut++];
        int i;
        int nx;
        int ny;

        if (cur.x == arr_x && cur.y == arr_y)
            return (1);
        i = 0;
        while (i < 4)
        {
            nx = cur.x + dir[i][0];
            ny = cur.y + dir[i][1];
            if (nx >= 0 && nx < LARGEUR && ny >= 0 && ny < HAUTEUR
                && !visite[ny][nx] && g_map[ny][nx] != '1')
            {
                visite[ny][nx] = 1;
                file[fin++] = (t_case){nx, ny};
            }
            i++;
        }
    }
    return (0);
}

int main(void)
{
    int dep_x;
    int dep_y;
    int arr_x;
    int arr_y;

    dep_x = -1;
    dep_y = -1;
    arr_x = -1;
    arr_y = -1;
    trouver_depart_arrivee(&dep_x, &dep_y, &arr_x, &arr_y);
    if (est_atteignable(dep_x, dep_y, arr_x, arr_y))
        printf("La sortie E est atteignable depuis P ✅\n");
    else
        printf("La sortie E est INATTEIGNABLE depuis P ❌\n");
    return (0);
}

