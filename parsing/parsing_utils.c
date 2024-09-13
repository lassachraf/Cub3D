/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:47:38 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/07 10:14:19 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*add_and_strdup(t_cub3D *game, void *pointer)
{
	char	*ret;

	ret = ft_strdup(pointer);
	gc_add(game, ret);
	return (ret);
}

void	ft_extension(t_cub3D *game, char *mapfile, char *ext)
{
	if (mapfile[ft_strlen(mapfile) - 1] == '\n')
		mapfile[ft_strlen(mapfile) - 1] = '\0';
	if (!access(mapfile, F_OK))
	{
		if (!ft_strncmp(&mapfile[ft_strlen(mapfile) - 4], ext, 5)
			&& ft_strlen(mapfile) > 4)
			return ;
		else
			ft_errors(game, "Error in extension.");
	}
	else
		ft_errors(game, "Error in file.");
}

int	is_map_element(char c)
{
	return (c == '1' || c == '0' || c == ' ' || c == 'D');
}

int	basic_checks(t_cub3D *game, t_map *map, char **line)
{
	if (!ft_strcmp(line[0], "\n"))
		return (map->start--, 1);
	if (line[2] && (!ft_strcmp(line[2], "\n") || ft_isspace(line[2][0])))
		line[2] = 0;
	else if (line[2])
		return (ft_errors(game, "Error on textures/colors2."), 0);
	if (!line || !line[0] || !line[1])
		return (ft_errors(game, "Error on textures/colors1."), 0);
	return (0);
}
