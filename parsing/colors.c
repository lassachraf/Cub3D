/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:34:34 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/25 12:36:32 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	ft_atoi_rgb(t_cub3D *game, char **str)
{
	int	nb;

	nb = 0;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '-')
		ft_errors(game, "Error 14.");
	if (**str == '+')
		(*str)++;
	while (ft_isdigit(**str))
	{
		nb = (nb * 10) + (((**str) - '0'));
		if (nb > 255)
			ft_errors(game, "Error 13.");
		(*str)++;
	}
	if (**str && !ft_isdigit(**str) && !ft_isspace(**str))
		ft_errors(game, "Error 12.");
	return (nb);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	ft_colors(t_cub3D *game, char *s)
{
	char	**split;
	int		rgb;
	int		r;
	int		g;
	int		b;

	split = ft_split(s, ',');
	add_split_to_gc(game, split);
	rgb = 0;
	r = ft_atoi_rgb(game, &split[0]);
	g = ft_atoi_rgb(game, &split[1]);
	b = ft_atoi_rgb(game, &split[2]);
	if (split[3])
		return (free_double(split), ft_errors(game, "Error 11."), 1);
	rgb = create_trgb(0, r, g, b);
	return (rgb);
}
