/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:10:18 by ttiprez           #+#    #+#             */
/*   Updated: 2025/11/26 15:49:51 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_file
{
	int				fd;
	char			*buf;
	size_t			buf_pos;
	ssize_t			buf_len;
	struct s_file	*next;
	struct s_file	*prev;
}	t_file;

char	*get_next_line(int fd);
t_file	*new_file(int fd);
t_file	*search_file(int fd, t_file **files);
ssize_t	read_file(t_file *file);
t_file	*free_file(t_file *file, t_file *files);

#endif
