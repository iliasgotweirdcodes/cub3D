/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:35:43 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/09/07 21:23:17 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (ft_putstr_fd("Error\nfilename too short!\n", 2), 0);
	if (ft_strncmp(&filename[len - 4], ".cub", 4) != 0)
		return (ft_putstr_fd("Error\nMap file must have .cub extension\n", 2), 0);
	return (1);
}
