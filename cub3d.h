/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilel-hla <ilel-hla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:22:26 by ilel-hla          #+#    #+#             */
/*   Updated: 2025/09/16 16:38:39 by ilel-hla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
# include <mlx.h>
#include "gnl/get_next_line.h"
#include <fcntl.h>

typedef struct s_cub
{
    void    *mlx;
    void    *win;
    char    **map;
    int		map_width;
	int		map_height;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color;
	int		ceiling_color;
    float     p_x;
    float     p_y;
    int     dir_y;
    int     dir_x;
    char    trend;
	void	*img;
	void	*img1;
    float   p_ang;
}   t_cub;

char    *get_next_line(int fd);
int	    ft_atoi(char *str);
int	    ft_strncmp(char *s1, char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strtrim(char *s1, char *set);
char	**ft_split(char *s, char c);
void	free_split(char **split);
void	free_cub(t_cub *cub);
void    free_textures(t_cub *cub);
void	free_map_rows(char **map, int rows);
int	    check_file_extension(char *filename);
int	    parse_cfg(t_cub *cub, int fd);
int	    read_map(char *file, t_cub *cub);
int	    check_valid_chars(t_cub *cub);
int	    check_one_player(t_cub *cub);
int	    check_surrounded_by_walls(t_cub *cub);
int     parse_map(t_cub *cub);
int	    is_map_line(char *line);
int	    map_height(char *file);
int	    map_width(char *file);
void	ft_error(t_cub *cub, char *line, char *msg, int fd);
void	print_map(t_cub *cub);
int	check_for_gaps(char *line);

#endif
