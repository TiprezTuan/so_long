/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:39:10 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/17 03:39:02 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool	pathfinder(t_map *map)
{
	t_pathfinder	finder;

	init_finder(map->map, &finder);
	return (find_way(map->map, &finder)); // Mettre message d'erreur
}



//	chatgpt
#include <stdio.h>

#define HAUTEUR 10
#define LARGEUR 10

char	g_map[HAUTEUR][LARGEUR + 1] = {
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
}	t_case;

void	trouver_depart_arrivee(int *dep_x, int *dep_y,
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

int	est_atteignable(int dep_x, int dep_y, int arr_x, int arr_y)
{
	int visite[HAUTEUR][LARGEUR] = {0}; // Initialise un tableau de toute les cases visites (y, x)
	t_case file[HAUTEUR * LARGEUR];		// La queue
	int debut = 0;
	int fin = 0;
	int dir[4][2] = {{0,-1},{0,1},{-1,0},{1,0}}; // 4 dirrections possibles;

	file[fin++] = (t_case){dep_x, dep_y}; // Ajoute la premiere case dans la queue des cases a visiter
	visite[dep_y][dep_x] = 1; // Dit que ca a ete visite
	while (debut < fin) // Tant qu'il reste des cases a visiter
	{
		t_case cur = file[debut++]; // Case courrante a visiter
		int i;
		int nx;
		int ny;

		if (cur.x == arr_x && cur.y == arr_y) // On a atteint l'arrive, le chemin est atteignable
			return (1);
		i = 0;
		while (i < 4) // 4 car on test les quatres directions (up, down, right, left)
		{
			nx = cur.x + dir[i][0]; // On par de cur et on ajoute le vecteure direction
			ny = cur.y + dir[i][1];
			if (nx >= 0 && nx < LARGEUR && ny >= 0 && ny < HAUTEUR 
				&& !visite[ny][nx] && g_map[ny][nx] != '1') // Si on est pas premier/dernier ligne ou debut/fin de ligne (les murs obligatoires)
			{
				visite[ny][nx] = 1; // La case a ete visitee donc on l'ajoute aux cases visitees
				file[fin++] = (t_case){nx, ny}; // On ajoute la nouvelle case a la queue
			}
			i++;
		}
	}
	return (0);
}

int	main(void)
{
	int	dep_x;
	int	dep_y;
	int	arr_x;
	int	arr_y;

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
