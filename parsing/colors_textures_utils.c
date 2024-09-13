/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_textures_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:46:07 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/06 14:36:01 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_atoi_rgb(t_cub3D *game, char *str)
{
	int	nb;

	nb = 0;
	if (!str)
		ft_errors(game, "Error on rgb atoi.");
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
		ft_errors(game, "Error negative color.");
	if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		nb = (nb * 10) + (((*str) - '0'));
		if (nb > 255)
			ft_errors(game, "Error higher color value.");
		str++;
	}
	if (*str && !ft_isdigit(*str) && !ft_isspace(*str))
		ft_errors(game, "Error on rgb atoi.");
	return (nb);
}

int	ft_colors(t_cub3D *game, char *s)
{
	char	**split;
	int		t;
	int		r;
	int		g;
	int		b;

	t = 0;
	split = ft_split(s, ',');
	add_split_to_gc(game, split);
	r = ft_atoi_rgb(game, split[0]);
	g = ft_atoi_rgb(game, split[1]);
	b = ft_atoi_rgb(game, split[2]);
	if (split[3])
	{
		free_double(split);
		return (ft_errors(game, "Error on ft_colors."), 1);
	}
	return (t << 24 | r << 16 | g << 8 | b);
}

void    set_texture(t_cub3D *game, t_map *map, char *texture, int flag)
{
	ft_extension(game, texture, ".xpm");
	if (flag == 1 && !map->n)
	{
		map->north = add_and_strdup(game, texture);
		map->n++;
	}
	else if (flag == 2 && !map->s)
	{
		map->south = add_and_strdup(game, texture);
		map->s++;
	}
	else if (flag == 3 && !map->e)
	{
		map->east = add_and_strdup(game, texture);
		map->e++;
	}
	else if (flag == 4 && !map->w)
	{
		map->west = add_and_strdup(game, texture);
		map->w++;
	}
	else
		ft_errors(game, "Error on setting textures.");
	map->counter = map->e + map->s + map->n + map->w + map->f + map->c;
}

void    set_color(t_cub3D *game, t_map *map, char *color, int flag)
{
	if (flag == 5 && !map->f)
	{
		map->floor = ft_colors(game, color);
		map->f++;
	}
	else if (flag == 6 && !map->c)
	{
		map->ceil = ft_colors(game, color);
		map->c++;
	}
	else
		ft_errors(game, "Error on setting colors");
	map->counter = map->e + map->s + map->n + map->w + map->f + map->c;
}

int	textures_and_colors_element(t_cub3D *game, t_map *map, char **line)
{
	if (basic_checks(game, map, line))
		return (1);
	if ((!ft_strcmp(line[0], "NO") || !ft_strcmp(line[0], "SO")
		|| !ft_strcmp(line[0], "EA") || !ft_strcmp(line[0], "WE")
		|| !ft_strcmp(line[0], "F") || !ft_strcmp(line[0], "C"))
		&& map->counter <= 6)
	{
		if (!ft_strcmp(line[0], "NO"))
			set_texture(game, map, line[1], 1);
		else if (!ft_strcmp(line[0], "SO"))
			set_texture(game, map, line[1], 2);
		else if (!ft_strcmp(line[0], "EA"))
			set_texture(game, map, line[1], 3);
		else if (!ft_strcmp(line[0], "WE"))
			set_texture(game, map, line[1], 4);
		else if (!ft_strcmp(line[0], "F"))
			set_color(game, map, line[1], 5);
		else if (!ft_strcmp(line[0], "C"))
			set_color(game, map, line[1], 6);
		return (1);
	}
	else
		return (ft_errors(game, "Error on textures/colors."), 0);
}
