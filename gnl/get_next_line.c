/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:41:08 by ilel-hla          #+#    #+#             */
/*   Updated: 2024/12/03 21:04:43 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = malloc(i + 2);
	else
		line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_remainder_line(char *buffer)
{
	int		i;
	int		j;
	char	*remainder;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	remainder = malloc(ft_strlen(buffer) - i + 1);
	if (!remainder)
		return (free (buffer), NULL);
	i++;
	while (buffer[i])
		remainder[j++] = buffer[i++];
	remainder[j] = '\0';
	free(buffer);
	return (remainder);
}

char	*ft_freejoin(char *buffer, char *n_buffer)
{
	char	*result;

	result = ft_strjoin(buffer, n_buffer);
	free (buffer);
	buffer = NULL;
	return (result);
}

char	*ft_read(int fd, char *buffer)
{
	char	*n_buffer;
	int		bytes_read;

	n_buffer = malloc(BUFFER_SIZE + 1);
	if (!n_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, n_buffer, BUFFER_SIZE);
		n_buffer[bytes_read] = '\0';
		buffer = ft_freejoin(buffer, n_buffer);
		if (!buffer)
			return (NULL);
		if (ft_strchr(n_buffer, '\n'))
			break ;
	}
	if (bytes_read == -1)
	{
		free(n_buffer);
		return (NULL);
	}
	free(n_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = get_remainder_line(buffer);
	if (!buffer)
		buffer = NULL;
	return (line);
}
