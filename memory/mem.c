/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:32:20 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/26 11:44:29 by alassiqu         ###   ########.fr       */
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

char	*freeing_join(char *s, char *s1)
{
	if (s1)
		free(s1);
	return (s);
}

void	clean_cub3D(t_cub3D *game)
{
	gc_free_all(game);
	free(game->gc);
	free(game);
}