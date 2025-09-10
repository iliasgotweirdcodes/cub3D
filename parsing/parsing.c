/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:25:23 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/09/09 21:40:57 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_cub(t_cub *cub)
{
	cub->map = NULL;
	cub->map_width = 0;
	cub->map_height = 0;
	cub->no_texture = NULL;
	cub->so_texture = NULL;
	cub->we_texture = NULL;
	cub->ea_texture = NULL;
	cub->floor_color = -1;
	cub->ceiling_color = -1;
	return (1);
}

void	print_map(t_cub *cub)
{
	printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", cub->no_texture, cub->so_texture, cub->we_texture, cub->ea_texture);
	printf("Floor color: %06X\nCeiling color: %06X\n", cub->floor_color, cub->ceiling_color);
	printf("height: %d, width: %d\n", cub->map_height, cub->map_width);
	int	i = 0;
	while (cub->map && cub->map[i])
	{
		printf("%s\n", cub->map[i]);
		i++;
	}
}

int	parsing(char *file, t_cub *cub)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\ncannot open file\n", 2), 0);
	if (!check_file_extension(file))
		return (0);
	init_cub(cub);
	parse_cfg(cub, fd);
	close(fd);
	if (!read_map(file, cub))
		return (free_textures(cub), ft_putstr_fd("Error\ninvalid map!\n", 2), 0);
	parse_map(cub);
	print_map(cub);
	free_cub(cub);
	return (1);
}

void x()
{
	system("lsof -c cub3D");
	system("leaks cub3D");
}
int main(int ac, char **av)
{
	// atexit(x);
	t_cub cub;

	if (ac != 2) 
        return (ft_putstr_fd("Usage: ./cub3D <mapfile.cub>\n", 2), 1);
    if (!parsing(av[1], &cub))
		return (1);
    return (0);
}