/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:25:21 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/09/08 23:46:03 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	get_cfg_type(char *line)
{
	int	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(line + i, "NO ", 3) == 0)
		return ('N');
	if (ft_strncmp(line + i, "SO ", 3) == 0)
		return ('S');
	if (ft_strncmp(line + i, "WE ", 3) == 0)
		return ('W');
	if (ft_strncmp(line + i, "EA ", 3) == 0)
		return ('E');
	if (ft_strncmp(line + i, "F ", 2) == 0)
		return ('F');
	if (ft_strncmp(line + i, "C ", 2) == 0)
		return ('C');
	return (0);
}

int	parse_texture(t_cub *cub, char *line, char *id, int fd)
{
	char	*trim;
	char	**dst;

	while (*line == ' ' || *line == '\t')
		line++;
	trim = ft_strtrim(line, " \t\n");
	if (!trim)
		ft_error(cub, NULL, "Failed to allocate memory for texture\n", fd);
	dst = NULL;
	if (ft_strncmp(id, "NO", 2) == 0)
		dst = &cub->no_texture;
	else if (ft_strncmp(id, "SO", 2) == 0)
		dst = &cub->so_texture;
	else if (ft_strncmp(id, "WE", 2) == 0)
		dst = &cub->we_texture;
	else if (ft_strncmp(id, "EA", 2) == 0)
		dst = &cub->ea_texture;
	else
	{
		free(trim);
		ft_error(cub, NULL, "Invalid texture identifier\n", fd);
	}
	if (*dst != NULL)
	{
		free(trim);
		ft_error(cub, NULL, "Duplicate texture config\n", fd);
	}
	*dst = trim;
	return (1);
}

int	valid_comma_count(char *line)
{
	int c;
	int j;

	if (!line)
		return (0);
	j = 0;
	c = 0;
	while (line[j])
	{
		if (line[j] == ',')
			c++;
		j++;
	}
	return (c == 2);
}

int	parse_color(t_cub *cub, char *line, char id, int fd)
{
	char	**split;
	int		rgb[3];
	int		i;
	int		color;
	char	*trim;

	while (*line == ' ' || *line == '\t')
		line++;
	split = ft_split(line, ',');
	if (!valid_comma_count(line) || !split || !split[0] || !split[1] || !split[2] || split[3])
	{
		free_split(split);
		ft_error(cub, NULL, "Color must have exactly three values separated by two commas\n", fd);
	}
	i = 0;
	while (i < 3)
	{
		trim = ft_strtrim(split[i], " \t\n\r");
		rgb[i] = ft_atoi(trim);
		free(trim);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free_split(split);
			ft_error(cub, NULL, "Color values must be between 0 and 255\n", fd);
		}
		i++;
	}
	free_split(split);
	color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	if (id == 'F')
		cub->floor_color = color;
	else if (id == 'C') 
		cub->ceiling_color = color;
	return (1);
}

int	check_config(t_cub *cub, char *line, int fd)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture(cub, line + 3, "NO", fd));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture(cub, line + 3, "SO", fd));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture(cub, line + 3, "WE", fd));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture(cub, line + 3, "EA", fd));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(cub, line + 2, 'F', fd));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(cub, line + 2, 'C', fd));
	return (0);
}

int	parse_cfg(t_cub *cub, int fd)
{
	int		count = 0;
	char	*line;
	char	*tmp;

	while ((line = get_next_line(fd)))
	{
		tmp = line;
		while (*tmp == ' ' || *tmp == '\t')
			tmp++;
		if (*tmp == '\n' || *tmp == '\0')
			free(line);
		else if (count < 6)
		{
			if (check_config(cub, line, fd))
				count++;
			free(line);
		}
		else if (get_cfg_type(tmp))
			ft_error(cub, line, "Too many configuration lines\n", fd);
		else
			free(line);
	}
	if (count != 6)
		ft_error(cub, NULL, "Invalid or missing configuration\n", fd);
	return (1);
}