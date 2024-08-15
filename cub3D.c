/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:42:38 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/15 16:03:05 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Memory part : Starts */

void	small_add_back(t_gc **gc, t_gc *new_node)
{
	t_gc	*curr;

	if (*gc)
	{
		curr = *gc;
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
	else
		*gc = new_node;
}

void	gc_add(t_cub3D *game, void *ptr)
{
	t_gc	*new_node;

	new_node = malloc(sizeof(t_gc));
	if (!new_node)
	{
		perror("Allocation failed.");
		exit(2);
	}
	new_node->ptr = ptr;
	new_node->next = NULL;
	small_add_back(&game->gc, new_node);
}

void	*ft_malloc(t_cub3D *game, size_t size)
{
	char	*memory;

	memory = malloc(size);
	if (!memory)
		return (ft_errors(game, "Allocation failed."), NULL);
	gc_add(game, memory);
	return (memory);
}

void	add_split_to_gc(t_cub3D *game, char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		gc_add(game, split[i]);
		i++;
	}
}

void	gc_free_all(t_cub3D *game)
{
	t_gc	*current;
	t_gc	*next;

	if (!game || !game->gc)
		return ;
	current = game->gc;
	while (current)
	{
		next = current->next;
		if (current->ptr)
			free(current->ptr);
		free(current);
		current = next;
	}
	game->gc = NULL;
}

/* Memory part : Ends */

/* Printing : Start */

void	ft_errors(t_cub3D *game, char *msg)
{
	printf(RED"%s\n"RESET, msg);
	if (game)
		gc_free_all(game);
	exit(1);
}

void	free_double(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);	
}

/* Printing : Start */

void	ft_extension(t_cub3D *game, char *argv, char *ext)
{
	if (access(argv, F_OK) == 0)
	{
		if (!strncmp(&argv[strlen(argv) - 4], ext, 5)
			&& strlen(argv) > 4)
			return ;
		else
			ft_errors(game, "Error.");
	}
	else
		ft_errors(game, "Error.");
}

char	*freeing_join(char *s, char *s1)
{
	if (s1)
		free(s1);
	return (s);
}

/* read from line :  */

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
		ft_errors(game, "Error.");
	}
	file = ft_split(lines, '\n');
	add_split_to_gc(game, file);
	return (free(lines), file);
}

// int	ft_colors(t_cub3D *game, char *s)
// {
// 	char	**split;

// 	split = ft_split(s, ',');
// }

int	check_textures(t_cub3D *game, t_map *map, char *s, int flag)
{
	if (!access(s, F_OK | R_OK))
	{
		if (flag != 5 && flag != 6)
			ft_extension(game, s, ".xpm");
		if (flag == 5 || flag == 6)
			ft_colors(game, s);
		if (flag == 1)
			map->north = ft_strdup(s);
		else if (flag == 2)
			map->south = ft_strdup(s);
		else if (flag == 3)
			map->west = ft_strdup(s);
		else if (flag == 4)
			map->east = ft_strdup(s);
		else if (flag == 5)
			map->floor = ft_strdup(s);
		else if (flag == 6)
			map->ceil = ft_strdup(s);
		return (1);
	}
	else
		ft_errors(game, "Error.");
	return (0);
}

int	one_of_map_elements(t_cub3D *game, t_map *map, char **s)
{
	if (!ft_strcmp(s[0], "NO") || !ft_strcmp(s[0], "SO")
		|| !ft_strcmp(s[0], "WE") || !ft_strcmp(s[0], "EA")
		|| !ft_strcmp(s[0], "F") || !ft_strcmp(s[0], "C"))
	{
		if (!ft_strcmp(s[0], "NO"))
			check_textures(game, map, s[1], 1);
		else if (!ft_strcmp(s[0], "SO"))
			check_textures(game, map, s[1], 2);
		else if (!ft_strcmp(s[0], "WE"))
			check_textures(game, map, s[1], 3);
		else if (!ft_strcmp(s[0], "EA"))
			check_textures(game, map, s[1], 4);
		return (1);
	}
	else
		return (0);
}

int	get_basic_elements(t_cub3D *game, t_map *map)
{
	char	**map_1;
	char	**value;
	int		counter;
	int		i;

	map_1 = map->file;
	counter = 0;
	i = -1;
	while (map_1[++i])
	{
		if (counter == 6)
			return (i);
		value = ft_split(map_1[i], ' ');
		add_split_to_gc(game, value);
		if (!value)
			continue;
		if (one_of_map_elements(game, map, value))
			counter++;
		else
			ft_errors(game, "Error.");
		free_double(value);
	}
	return (0);
}

char	**get_map(t_cub3D *game, t_map *map, int start)
{
	char	**map_1;
	char	**map_1;
	int		i;

	i = start;
	map_1 = map->file;
	while (map_1[i])
	{
		
	}
}

void	ft_check_map(t_cub3D *game, t_map *map, char *mapfile)
{
	int	start;

	map->fd = open(mapfile, O_RDONLY);
	if (map->fd < 0)
		ft_errors(game, "Error.");
	map->file = get_file_content(game, map->fd);
	start = get_basic_elements(game, map);
	printf("start >> %d\n", start);
	map->map = get_map(game, map, start);
}

t_cub3D	*all_check(t_cub3D *game, char *mapfile)
{
	t_map		*map;

	map = malloc(sizeof(t_map));
	if (!map)
		ft_errors(game, "Malloc error.");
	gc_add(game, map);
	ft_bzero(map, sizeof(t_map));
	ft_extension(game, mapfile, ".cub");
	ft_check_map(game, map, mapfile);
	game->map = map;
	return (game);
}

void    init_game(t_cub3D *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1920, 1080,"Cub3D !");
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	(void)av;
	t_cub3D	*game;
	t_gc	*gc;

	gc = NULL;
	game = NULL;
	if (ac != 2)
		ft_errors(NULL, "Arg Error : Expected 2 args.");
	game = (t_cub3D *)malloc(sizeof(t_cub3D));
	if (!game)
		ft_errors(NULL, "Allocation failed.");
	ft_bzero(game, (sizeof(game)));
	gc = (t_gc *)malloc(sizeof(t_gc));
	if (!gc)
		ft_errors(NULL, "Allocation failed.");
	ft_bzero(gc, (sizeof(gc)));
	game->gc = gc;
	game = all_check(game, av[1]);
	// init_game(game);
	// gc_free_all(game);
	return (0);
}
