/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:54:21 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/29 14:31:50 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	get_map_info(t_cub3D *game, char **map, int i, int *h)
{
	int	w;
	int	k;
	int	j;

	j = i;
	w = 0;
	while (map[j])
	{
		k = 0;
		check_first_element(game, map, &j, &k);
		while (map[j][k])
			k++;
		check_last_element(game, map[j]);
		if (w < k)
			w = k;
		j++;
	}
	*h = j - i;
	return (w);
}

char	**alloc_and_fill_map(t_cub3D *game, char **map_1, int w, int h)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	map = ft_malloc(game, (sizeof(char *) * (h + 1)));
	while (map_1[i] && i < h)
	{
		map[i] = ft_malloc(game, sizeof(char) * (w + 1));
		ft_strncpy_2(map[i++], map_1[j++], w);
	}
	map[h] = 0;
	return (map);
}

void	check_map_element(t_cub3D *game, t_map *map)
{
	char	**s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = map->map;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			is_valid_element(game, map, s[i][j]);
			j++;
		}
		i++;
	}
	i = map->e + map->s + map->n + map->w;
	if (i != 1)
		ft_errors(game, "Error 5.");
}

char	**get_map(t_cub3D *game, t_map *map, int start)
{
	char	**map_1;
	char	**map_2;
	int		height;
	int		i;

	i = start;
	height = 0;
	map_1 = map->file;
	skip_white_lines(map_1, &i);
	if (!map_1[i])
		ft_errors(game, "Error 2.");
	map->width = get_map_info(game, map_1, i, &(map->height));
	map_2 = alloc_and_fill_map(game, &map_1[i], map->width, map->height);
	check_surrounded(game, map_2, map->height, map->width);
	map->map = map_2;
	return (map_2);
}

void	ft_check_map(t_cub3D *game, t_map *map, char *mapfile)
{
	int	start;

	start = 0;
	map->fd = open(mapfile, O_RDONLY);
	if (map->fd < 0)
		ft_errors(game, "Error 1.");
	map->file = get_file_content(game, map->fd);
	close(map->fd);
	start = get_basic_elements(game, map);
	map->map = get_map(game, map, start);
	game->map = map;
}
