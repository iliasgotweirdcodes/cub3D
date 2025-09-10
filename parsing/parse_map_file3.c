/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 23:31:21 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/09/09 21:40:48 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_valid_chars(t_cub *cub)
{
    int i, j;
    char c;

    i = 0;
    while (cub->map[i])
    {
        j = 0;
        while ((c = cub->map[i][j]))
        {
            if (!(c == '1' || c == '0' || c == 'N' || c == 'S' 
				|| c == 'E' || c == 'W' || c == ' '))
                ft_error(cub, NULL, "Invalid character in map\n", -1);
            j++;
        }
        i++;
    }
    return (1);
}

int	check_one_player(t_cub *cub)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (cub->map && cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'W' || cub->map[i][j] == 'E' ||
				cub->map[i][j] == 'N' || cub->map[i][j] == 'S')
				p++;
			j++;
		}
		i++;
	}
	if (p != 1)
		ft_error(cub, NULL, "There must be exactly one player inside the map\n", -1);
	return (1);
}

int	check_surrounded_by_walls(t_cub *cub)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < cub->map_height)
	{
		x = 0;
		while (x < cub->map_width)
		{
			c = cub->map[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (y == 0 || y == cub->map_height - 1 || x == 0 || x == cub->map_width - 1)
					ft_error(cub, NULL, "Map not surrounded by walls\n", -1);
				if (cub->map[y - 1][x] == ' ' || cub->map[y + 1][x] == ' ' ||
					cub->map[y][x - 1] == ' ' || cub->map[y][x + 1] == ' ')
					ft_error(cub, NULL, "Map not surrounded by walls\n", -1);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	parse_map(t_cub *cub)
{
	check_valid_chars(cub);
	check_one_player(cub);
	check_surrounded_by_walls(cub);
	return (1);
}