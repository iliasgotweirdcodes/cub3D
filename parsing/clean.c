/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:52:54 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/09/07 21:18:35 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_split(char **split)
{
	int i;

	if (!split)
		return;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void free_textures(t_cub *cub)
{
	if (cub->no_texture)
		free(cub->no_texture);
	if (cub->so_texture)
		free(cub->so_texture);
	if (cub->we_texture)
		free(cub->we_texture);
	if (cub->ea_texture)
		free(cub->ea_texture);
	free(cub->map);
}

void free_cub(t_cub *cub)
{
	int i;

    if (!cub)
        return;
	i = 0;
    if (cub->no_texture)
        free(cub->no_texture);
    if (cub->so_texture)
        free(cub->so_texture);
    if (cub->we_texture)
        free(cub->we_texture);
    if (cub->ea_texture)
        free(cub->ea_texture);
    if (cub->map)
    {
        while (cub->map[i])
        {
            free(cub->map[i]);
            cub->map[i] = NULL;
            i++;
        }
        free(cub->map);
        cub->map = NULL;
    }
}

void	free_map_rows(char **map, int rows)
{
	int	j;

	j = 0;
	while (j < rows)
	{
		free(map[j]);
		j++;
	}
}

void	ft_error(t_cub *cub, char *line, char *msg, int fd)
{
	if (fd >= 0)
		close(fd);
	if (line)
		free(line);
	if (cub)
		free_cub(cub);
	if (msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(msg, 2);
	}
	exit(1);
}
