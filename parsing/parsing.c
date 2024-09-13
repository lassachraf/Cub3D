/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:42:13 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/13 20:39:09 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_get_map(t_cub3D *game, t_map *map)
{
	char	**content;
	int		i;
	int		j;

	content = map->file;
	while (!ft_strcmp(content[map->start], " "))
		map->start++;
	i = map->start;
	if (!content[i])
		ft_errors(game, "Error getting map.");
	while (content[i])
	{
		j = 0;
		while (content[i][j] && is_map_element(content[i][j]))
			j++;
		if (is_map_element(content[i][j]))
			ft_errors(game, "Error on map element.");
		if (map->width < j)
			map->width = j;
		i++;
	}
	map->height = i - map->start;
	alloc_and_fill_map(game, map);
	check_surrounded(game, map);
	game->map = map;
}

void	ft_get_player(t_cub3D *game, t_player *player)
{
	int	i;
	int	j;

	i = -1;
	player->radius = 2;
	player->movespeed = 0.2;
	player->rotationspeed = 3 * (PI / 180);
	while (game->map->map[++i])
	{
		j = -1;
		while (game->map->map[i][++j])
		{
			if (is_it_player(game->map->map[i][j]))
			{
				player->x = j;
				player->y = i;
				player->count++;
			}
		}
	}
	if (player->count != 1)
		ft_errors(game, "Error more than one player.");
	adjust_rotation(player, game->map->map);
	game->player = player;
}

void	store_file_content(t_cub3D *game, t_map *map, t_player *player)
{
	char	*line;
	char	**file;
	char	*lines;

	lines = NULL;
	line = get_next_line(map->fd);
	while (line)
	{
		if (!line)
			break ;
		if (map->counter != 6)
			map->start++;
		parse_line(game, map, &line);
		lines = free_and_join(line, &lines);
		free(line);
		line = get_next_line(map->fd);
	}
	if (!lines)
		ft_errors(game, "Error P3.");
	file = ft_split(lines, '\n');
	free(lines);
	add_split_to_gc(game, file);
	map->file = file;
	ft_get_map(game, map);
	ft_get_player(game, player);
}

void	ft_whole_map(t_cub3D *game, t_map *map, t_player *player, char *mapfile)
{
	ft_extension(game, mapfile, ".cub");
	map->fd = open(mapfile, O_RDONLY);
	if (map->fd < 0)
		ft_errors(game, "Error P1.");
	store_file_content(game, map, player);
	close(map->fd);
}

t_cub3D	*parsing(t_cub3D *game, char *av)
{
	t_map		*map;
	t_player	*player;

	map = malloc(sizeof(t_map));
	if (!map)
		ft_errors(game, "Allocation failed.");
	ft_bzero(map, sizeof(t_map));
	gc_add(game, map);
	player = malloc(sizeof(t_player));
	if (!player)
		ft_errors(game, "Allocation failed.");
	ft_bzero(player, sizeof(t_player));
	gc_add(game, player);
	ft_whole_map(game, map, player, av);
	return (game);
}
