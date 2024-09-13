/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_and_indexes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:19:48 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/11 11:20:02 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

float	normalize_angle(float angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0)
		angle += (2 * PI);
	return (angle);
}

int	get_y_index(float y)
{
	return ((int)((y / TILE_SIZE) * TILE_SIZE));
}

int	get_x_index(t_cub3D *game, float y, float yint, int id)
{
	float	x;

	x = (y - yint) / tan(game->rays->lst_of_rays[id].ray_angle);
	return ((int)(game->player->x + x));
}
