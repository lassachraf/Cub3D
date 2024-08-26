/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:20:52 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/26 18:32:06 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_textures(t_cub3D *game, t_map *map, char *s, int flag)
{
	if (flag != 5 && flag != 6 && !access(s, F_OK | R_OK))
	{
		ft_extension(game, s, ".xpm");
		if (flag == 1)
			map->north = ft_strdup(s);
		else if (flag == 2)
			map->south = ft_strdup(s);
		else if (flag == 3)
			map->west = ft_strdup(s);
		else if (flag == 4)
			map->east = ft_strdup(s);
		return (add_to_gc(game, map, flag), 1);
	}
	else if (flag == 5 || flag == 6)
	{
		if (flag == 5)
			map->floor = ft_colors(game, s);
		else
			map->ceil = ft_colors(game, s);
	}
	else
		ft_errors(game, "Error 10.");
	return (0);
}

int	one_of_map_elements(t_cub3D *game, t_map *map, char **s)
{
	if (!ft_strcmp(s[0], "NO") || !ft_strcmp(s[0], "SO")
		|| !ft_strcmp(s[0], "WE") || !ft_strcmp(s[0], "EA")
		|| !ft_strcmp(s[0], "F") || !ft_strcmp(s[0], "C"))
	{
		if (!ft_strcmp(s[0], "NO"))
			check_textures(game, map, s[1], 1);
		else if (!ft_strcmp(s[0], "SO"))
			check_textures(game, map, s[1], 2);
		else if (!ft_strcmp(s[0], "WE"))
			check_textures(game, map, s[1], 3);
		else if (!ft_strcmp(s[0], "EA"))
			check_textures(game, map, s[1], 4);
		else if (!ft_strcmp(s[0], "F"))
			check_textures(game, map, s[1], 5);
		else if (!ft_strcmp(s[0], "C"))
			check_textures(game, map, s[1], 6);
		return (1);
	}
	else
		return (0);
}

int	get_basic_elements(t_cub3D *game, t_map *map)
{
	char	**map_1;
	char	**value;
	int		counter;
	int		i;

	map_1 = map->file;
	counter = 0;
	i = -1;
	while (map_1[++i])
	{
		if (counter == 6)
			return (i);
		value = ft_split(map_1[i], ' ');
		add_split_to_gc(game, value);
		if (!value)
			continue;
		if (one_of_map_elements(game, map, value))
			counter++;
		else
			ft_errors(game, "Error 9.");
	}
	if (counter != 6)
		ft_errors(game, "Error 100.");
	return (0);
}

int	is_it_player(char c)
{
	return (c == 'W' || c == 'N' || c == 'S' || c == 'E');
}

void	set_player_info(t_cub3D *game, t_player *player)
{
	int	i;
	int	j;

	i = -1;
	player->radius = 2;
	player->movespeed = 3;
	player->rotationspeed = 3 * (PI / 180);
	player->rotationangle = (PI / 2);
	while (game->map->map[++i])
	{
		j = -1;
		while (game->map->map[i][++j])
		{
			if (is_it_player(game->map->map[i][j]))
			{
				player->x = i;
				player->y = j;
			}
		}
	}
	game->player = player;	
}

t_cub3D	*all_check(t_cub3D *game, char *mapfile)
{
	t_map		*map;
	t_player	*player;

	map = malloc(sizeof(t_map));
	if (!map)
		ft_errors(game, "Malloc error.");
	gc_add(game, map);
	player = malloc(sizeof(t_player));
	if (!player)
		ft_errors(game, "Malloc error.");
	ft_bzero(map, sizeof(t_player));
	ft_extension(game, mapfile, ".cub");
	ft_check_map(game, map, mapfile);
	set_player_info(game, player);
	return (game);
}
