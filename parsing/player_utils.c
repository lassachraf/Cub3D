/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:48:53 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/06 14:25:20 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_it_player(char c)
{
	return (c == 'W' || c == 'N' || c == 'S' || c == 'E');
}

void	adjust_rotation(t_player *player, char **map)
{
	if (map[(int)player->y][(int)player->x] == 'N')
		player->rotationangle = -PI / 2;
	else if (map[(int)player->y][(int)player->x] == 'S')
		player->rotationangle = PI / 2;
	else if (map[(int)player->y][(int)player->x] == 'E')
		player->rotationangle = 0;
	else if (map[(int)player->y][(int)player->x] == 'W')
		player->rotationangle = PI;
}
