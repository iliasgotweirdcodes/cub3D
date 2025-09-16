/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:28:18 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/09/10 20:43:19 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*skip_to_first_map_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && !is_map_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

char	*pad_line(char *src, int width)
{
	char	*dst;
	int		i;

	dst = (char *)malloc(width + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n' && i < width)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < width)
	{
		dst[i] = 32;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	validate_bottom_lines(int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
				return (free(line), 0);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	check_for_gaps(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] != ' ' && line[j] != '\t' && line[j] != '\n')
			return (1);
		j++;
	}
	return (0);
}

int	read_map(char *file, t_cub *cub)
{
	int		fd;
	char	*line;
	int		i;

	cub->map_width = map_width(file);
	cub->map_height = map_height(file);
	if (cub->map_width == 0 || cub->map_height == 0)
		ft_error(cub, NULL, "Map not found!\n", -1);
	cub->map = (char **)malloc(sizeof(char *) * (cub->map_height + 1));
	if (!cub->map)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = skip_to_first_map_line(fd);
	i = 0;
	while (line && i < cub->map_height)
	{
		if (!check_for_gaps(line))
			return (free(line), free_map_rows(cub->map, i), close(fd), 0);
		cub->map[i] = pad_line(line, cub->map_width);
		if (!cub->map[i])
			return (free(line), free_map_rows(cub->map, i), close(fd), 0);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	cub->map[i] = NULL;
	if (!validate_bottom_lines(fd))
		return (free_map_rows(cub->map, i), close(fd), 0);
	return (close(fd), 1);
}
