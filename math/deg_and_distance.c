/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deg_and_rad.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:18:06 by alassiqu          #+#    #+#             */
/*   Updated: 2024/09/11 11:18:37 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

long	deg_to_rad(long deg)
{
	return (deg * (PI / 180));
}

long	rad_to_deg(long rad)
{
	return (rad * (180 / PI));
}

long	twopointsdistance(int ax, int ay, int bx, int by)
{
	return (sqrt(pow((bx - ax), 2) + pow((by - ay), 2)));
}
