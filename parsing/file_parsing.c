/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:56:27 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/26 10:05:07 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_extension(t_cub3D *game, char *argv, char *ext)
{
	if (access(argv, F_OK) == 0)
	{
		if (!strncmp(&argv[strlen(argv) - 4], ext, 5)
			&& strlen(argv) > 4)
			return ;
		else
			ft_errors(game, "Error 17.");
	}
	else
		ft_errors(game, "Error 16.");
}

char	**get_file_content(t_cub3D *game, int fd)
{
	char	*line;
	char	**file;
	char	*lines;

	lines = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!line)
			break ;
		lines = freeing_join(ft_strjoin(lines, line), lines);
		free(line);
		line = get_next_line(fd);
	}
	if (!lines)
	{
		ft_errors(game, "Error 15.");
	}
	file = ft_split(lines, '\n');
	add_split_to_gc(game, file);
	return (free(lines), file);
}

int	skip_white_lines(char **s, int *i)
{
	while ((*s)[(*i)])
	{
		if (ft_isspace((*s)[*i]))
		{
			while ((*s)[*i] && ft_isspace((*s)[*i]))
				(*i)++;
		}
		if (!(*s)[*i])
			(*i)++;
		else
			break ;
	}
	return (0);
}

void	skip_whitespaces(char *s, int *i)
{
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
}
