/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:35:33 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/09/09 22:30:44 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 0 || line[i] == '\n')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'E'
			&& line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	is_config_line(char *line)
{
	int	i;

    i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return ((line[i] == 'N' && line[i+1] == 'O') ||
		(line[i] == 'S' && line[i+1] == 'O') ||
		(line[i] == 'W' && line[i+1] == 'E') ||
		(line[i] == 'E' && line[i+1] == 'A') ||
		(line[i] == 'F') || (line[i] == 'C'));
}

char	*skip_config_lines(int fd, int cfg_count)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line && count < cfg_count)
	{
		if (is_config_line(line))
			count++;
		free(line);
		if (count < cfg_count)
			line = get_next_line(fd);
	}
	return (line);
}

// int map_height(char *file)
// {
//     int     fd;
//     char    *line;
//     int     count;
//     int     i;

//     fd = open(file, O_RDONLY);
//     if (fd < 0)
//         return (0);
//     i = 0;
//     count = 0;
//     line = skip_config_lines(fd, 6);
//     while ((line = get_next_line(fd)))
//     {
//         if (is_map_line(line))
//             count++;
//         free(line);
//         i++;
//     }
//     close(fd);
//     return (count);
// }

int map_height(char *file)
{
    int fd;
    char *line;
    int count;
    int started;

    count = 0;
    started = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (0);
    while ((line = get_next_line(fd)))
    {
        // skip config lines and empty lines at start
        if (!started && !is_map_line(line))
        {
            free(line);
            continue;
        }
        started = 1;
        // stop counting at first empty line after map starts
        if (started && !check_for_gaps(line))
        {
            free(line);
            break;
        }
        count++;
        free(line);
    }
    return (close(fd), count);
}

// int map_width(char *file)
// {
//     int     fd;
//     char    *line;
//     int     max_width;
//     int     len;

//     fd = open(file, O_RDONLY);
//     if (fd < 0)
//         return 0;
//     max_width = 0;
//     line = skip_config_lines(fd, 6);
//     while ((line = get_next_line(fd)))
//     {
//             len = 0;
//             while (line[len] && line[len] != '\n')
//                 len++;
//             if (len > max_width)
//                 max_width = len;
//         free(line);
//     }
//     close(fd);
//     return (max_width);
// }

int map_width(char *file)
{
    int  fd;
    char *line;
    int  max_width;
    int  started;
    int  len;

    max_width = 0;
    started = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (0);
    while ((line = get_next_line(fd)))
    {
        // Skip config lines until we hit the first map line
        if (!started && !is_map_line(line))
        {
            free(line);
            continue;
        }
        started = 1;
        // Stop at first completely empty line after map starts
        if (started && !check_for_gaps(line))
        {
            free(line);
            break;
        }
        len = 0;
        while (line[len] && line[len] != '\n')
            len++;
        if (len > max_width)
            max_width = len;
        free(line);
    }
    return (close(fd), max_width);
}
