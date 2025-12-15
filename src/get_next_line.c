/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:11:58 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/15 13:33:46 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	finalize_line(char *line, t_file *file)
{
	size_t	i;

	i = 0;
	while (line && line[i] && line[i] != '\n')
		i++;
	if ((line && line[i] == '\n'))
		return (1);
	if (!file || file->buf_len <= 0)
		return (1);
	return (0);
}

static void	expand_line(char *new_line, char *l, t_file *file, size_t new_len)
{
	size_t	i;
	size_t	line_len;

	i = 0;
	while (l && l[i])
	{
		new_line[i] = l[i];
		i++;
	}
	line_len = i;
	i = 0;
	while (i < new_len)
	{
		new_line[line_len + i] = file->buf[file->buf_pos + i];
		i++;
	}
	new_line[line_len + i] = '\0';
	file->buf_pos += i;
}

static char	*add_char_to_line(char *line, t_file *file)
{
	char	*new_line;
	size_t	line_len;
	size_t	len_to_add;

	if ((ssize_t)file->buf_pos >= file->buf_len && read_file(file) < 0)
		return (free(line), NULL);
	line_len = 0;
	while (line && line[line_len])
		line_len++;
	len_to_add = 0;
	while (file->buf[file->buf_pos + len_to_add]
		&& file->buf[file->buf_pos + len_to_add] != '\n')
		len_to_add++;
	if (file->buf[file->buf_pos + len_to_add] == '\n')
		len_to_add++;
	if (line_len + len_to_add <= 0)
		return (free(line), NULL);
	new_line = malloc(line_len + len_to_add + 1);
	if (!new_line)
		return (free(line), NULL);
	expand_line(new_line, line, file, len_to_add);
	free(line);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static t_file	*files;
	char			*line;
	t_file			*file;

	file = search_file(fd, &files);
	if (!file)
		return (NULL);
	line = add_char_to_line(NULL, file);
	while (line && !finalize_line(line, file))
		line = add_char_to_line(line, file);
	if (file && !line)
		files = free_file(file, files);
	return (line);
}
