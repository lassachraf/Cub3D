/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:32:20 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/13 20:39:33 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	add_to_gc(t_cub3D *game, t_map *map, int flag)
{
	if (flag == 1)
		gc_add(game, map->north);
	else if (flag == 2)
		gc_add(game, map->south);
	else if (flag == 3)
		gc_add(game, map->west);
	else if (flag == 4)
		gc_add(game, map->east);
}

void	free_double(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);	
}

char	*free_and_join(char *line, char **lines)
{
	char	*ret;

	ret = ft_strjoin(*lines, line);
	if (*lines)
		free(*lines);
	return (ret);
}

void	clean_cub3D(t_cub3D *game)
{
	gc_free_all(game);
	free(game->gc);
	free(game);
}
