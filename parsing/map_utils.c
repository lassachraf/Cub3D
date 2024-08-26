/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:08:41 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/26 10:19:52 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_valid_element(t_cub3D *game, t_map *map, char c)
{
	if (c == ' ' || c == '1' || c == '0' || c == 'D')
		return (1);
	else if (c == 'W' || c == 'N' || c == 'S' || c == 'E')
	{
		if (c == 'W')
			map->w++;
		else if (c == 'N')
			map->n++;
		else if (c == 'E')
			map->e++;
		else if (c == 'S')
			map->s++;
		return (1);
	}
	else
		ft_errors(game, "Error 8.");
	return (0);
}

void	check_first_element(t_cub3D *game, char **map, int *j, int *k)
{
	skip_whitespaces(map[*j], k);
	if (map[*j][*k] != '1')
		ft_errors(game, "Error 7.");
}

int	check_last_element(t_cub3D *game, char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	if (ft_isspace(s[i]))
	{
		while (s[i] && ft_isspace(s[i]))
			i--;
	}
	if (s[i] == '1')
		return (1);
	else
		ft_errors(game, "Error 86.");
	return (1);
}

void	check_surrounded(t_cub3D *game, char **map, int nb_line, int col_len)
{
	int	i;
	int	j;

	i = -1;
	while (++i < nb_line)
	{
		j = -1;
		while (++j < col_len)
		{
			if (map[i][j] == '0' || map[i][j] == 'D')
			{
				if (i == 0 || i == nb_line - 1 || j == 0 || j == col_len - 1)
					ft_errors(game, "Error 407.");
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j
					- 1] == ' ' || map[i][j + 1] == ' ')
					ft_errors(game, "Error 408.");
			}
			if (map[i][j] == 'D')
			{
				if (!((map[i - 1][j] == '1' && map[i + 1][j] == '1') || map[i][j
						- 1] == '1' || map[i][j + 1] == '1'))
					ft_errors(game, "Error 409.");
			}
		}
	}
}

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
