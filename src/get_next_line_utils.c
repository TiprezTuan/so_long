/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:10:23 by ttiprez           #+#    #+#             */
/*   Updated: 2025/12/15 11:09:42 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_file	*new_file(int fd)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	file->buf = malloc(BUFFER_SIZE + 1);
	if (!file->buf)
		return (free(file), NULL);
	file->fd = fd;
	file->prev = NULL;
	file->next = NULL;
	read_file(file);
	return (file);
}

t_file	*search_file(int fd, t_file **files)
{
	t_file	*current_file;
	t_file	*file;

	current_file = *files;
	while (current_file && current_file->next && current_file->fd != fd)
		current_file = current_file->next;
	if (current_file && current_file->fd == fd)
		return (current_file);
	file = new_file(fd);
	if (!file)
		return (NULL);
	if (!*files)
		return (*files = file);
	file->prev = current_file;
	current_file->next = file;
	return (file);
}

ssize_t	read_file(t_file *file)
{
	file->buf_pos = 0;
	file->buf_len = read(file->fd, file->buf, BUFFER_SIZE);
	if (file->buf_len >= 0)
		file->buf[file->buf_len] = '\0';
	return (file->buf_len);
}

t_file	*free_file(t_file *file, t_file *files)
{
	if (!file)
		return (files);
	if (file->prev)
		file->prev->next = file->next;
	else
		files = file->next;
	if (file->next)
		file->next->prev = file->prev;
	free(file->buf);
	free(file);
	return (files);
}
