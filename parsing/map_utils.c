/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:44:16 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/15 10:09:38 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*ft_strncpy_2(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = ' ';
		i++;
	}
	dest[i] = 0;
	return (dest);
}

void	alloc_and_fill_map(t_cub3D *game, t_map *map)
{
	int		i;
	int		j;
	char	**ret;
	char	**cpy_map;

	i = 0;
	j = 0;
	cpy_map = &map->file[map->start];
	ret = ft_malloc(game, (sizeof(char *) * (map->height + 1)));
	while (cpy_map[i] && i < map->height)
	{
		ret[i] = ft_malloc(game, sizeof(char) * (map->width + 1));
		ft_strncpy_2(ret[i++], cpy_map[j++], map->width);
	}
	ret[map->height] = 0;
	map->map = ret;
}

void	general_check(t_cub3D *game, t_map *maps, int *i, int *j)
{
	char	**s;

	s = maps->map;
	if (s[*i][*j] == '0' || s[*i][*j] == 'D' || is_it_player(s[*i][*j]))
	{
		if (*i == 0 || *i == maps->height - 1 || *j == 0
			|| *j == maps->width - 1)
			ft_errors(game, "Error: unsurrounded map.");
		if (s[(*i) - 1][*j] == ' ' || s[(*i) + 1][*j] == ' '
			|| s[*i][*j - 1] == ' ' || s[*i][*j + 1] == ' ')
			ft_errors(game, "Error: invalid map.");
	}
	if (s[*i][*j] == 'D')
	{
		if (!((s[*i - 1][*j] == '1' && s[*i + 1][*j] == '1')
			|| (s[*i][*j - 1] == '1' && s[*i][*j + 1] == '1')))
			ft_errors(game, "Error: useless door position.");
	}
}

void	check_surrounded(t_cub3D *game, t_map *maps)
{
	int	i;
	int	j;

	i = -1;
	while (++i < maps->height)
	{
		j = -1;
		while (++j < maps->width)
			general_check(game, maps, &i, &j);
	}
}

void	parse_line(t_cub3D *game, t_map *map, char **line)
{
	char	**value;

	value = NULL;
	if (*line[0] == '\n' && map->counter == 6)
	{
		free(*line);
		*line = ft_strdup(" \n");
		return ;
	}
	value = ft_split(*line, ' ');
	if (!value)
		return ;
	add_split_to_gc(game, value);
	if (map->counter < 6 && !textures_and_colors_element(game, map, value))
		ft_errors(game, "Error: invalid texture.");
	if (map->counter > 6)
		ft_errors(game, "Error: duplicated texture.");
}
