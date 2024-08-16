/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:42:38 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/16 15:46:43 by alassiqu         ###   ########.fr       */
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

void	print_map_info(t_map *map)
{
	char	**s;
	int		i;

	i = 0;
	printf("/* Map infos after check */\n");
	printf("/* ceil  > %d */\n", map->ceil);
	printf("/* east  > %s */\n", map->east);
	printf("/* west  > %s */\n", map->west);
	printf("/* north > %s */\n", map->north);
	printf("/* floor > %d */\n", map->floor);
	printf("/* south > %s */\n", map->south);
	s = map->map;
	printf("/* --------------- MAP --------------- */\n");
	while (s[i])
	{
		printf("|*%s*|\n", s[i]);
		i++;
	}
	printf("/* --------------- MAP --------------- */\n");
}

/* Printing : Ends */

/* Free : Start */

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

/* Free : Ends */

/* Parsing : Start */

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

/* Parsing : Ends */

/* Map : Start */

int	ft_atoi_rgb(t_cub3D *game, char **str)
{
	int	nb;

	nb = 0;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '-')
		ft_errors(game, "Error.");
	if (**str == '+')
		(*str)++;
	while (ft_isdigit(**str))
	{
		nb = (nb * 10) + (((**str) - '0'));
		if (nb > 255)
			ft_errors(game, "Error.");
		(*str)++;
	}
	if (**str && !ft_isdigit(**str) && !ft_isspace(**str))
		ft_errors(game, "Error.");
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
	rgb = 0;
	r = ft_atoi_rgb(game, &split[0]);
	g = ft_atoi_rgb(game, &split[1]);
	b = ft_atoi_rgb(game, &split[2]);
	if (split[3])
		return (free_double(split), ft_errors(game, "Error."), 1);
	rgb = create_trgb(0, r, g, b);
	return (rgb);
}

int	check_textures(t_cub3D *game, t_map *map, char *s, int flag)
{
	if (flag != 5 && flag != 6 && !access(s, F_OK | R_OK))
	{
		ft_extension(game, s, ".xpm");
		if (flag == 1)
			map->north = ft_strdup(s);
		else if (flag == 2)
			map->south = ft_strdup(s);
		else if (flag == 3)
			map->west = ft_strdup(s);
		else if (flag == 4)
			map->east = ft_strdup(s);
		return (1);
	}
	else if (flag == 5 || flag == 6)
	{
		if (flag == 5)
			map->floor = ft_colors(game, s);
		else
			map->ceil = ft_colors(game, s);
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
		else if (!ft_strcmp(s[0], "F"))
			check_textures(game, map, s[1], 5);
		else if (!ft_strcmp(s[0], "C"))
			check_textures(game, map, s[1], 6);
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
	}
	return (0);
}

int	is_valid_element(t_cub3D *game, t_map *map, char c)
{
	if (c == ' ' || c == '1' || c == '0')
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
		ft_errors(game, "Error.");
	return (0);
}

int	get_map_info(t_cub3D *game, char **map_1, int i, int *h)
{
	int	w;
	int	k;
	int	j;

	j = i;
	w = 0;
	while (map_1[j])
	{
		k = 0;
		skip_whitespaces(map_1[j], &k);
		if (map_1[j][k] != '1')
			ft_errors(game, "Error.");
		while (map_1[j][k])
			k++;
		if (w < k)
			w = k;
		j++;
	}
	*h = j - i;
	return (w);
}

char	*ft_strncpy_2(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = ' ';
		i++;
	}
	return (dest);
}

char	**alloc_and_fill_map(t_cub3D *game, char **map_1, int w, int h)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	map = ft_malloc(game, (sizeof(char *) * (h + 1)));
	while (map_1[i] && i < h)
	{
		map[i] = ft_malloc(game, sizeof(char) * (w + 1));
		ft_strncpy_2(map[i++], map_1[j++], w);
		map[w + 1] = 0;
	}
	map[h] = 0;
	return (map);
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
		ft_errors(game, "Error.");
	return (1);
}

void	check_map_element(t_cub3D *game, t_map *map)
{
	char	**s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = map->map;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			is_valid_element(game, map, s[i][j]);
			j++;
		}
		i++;
	}
	i = map->e + map->s + map->n + map->w;
	if (i != 1)
		ft_errors(game, "Error.");
}

void	whole_map_check(t_cub3D *game, t_map *map, int h)
{
	char	**s;
	int		i;

	i = 0;
	s = map->map;
	check_map_element(game, map);
	/* CHECK1 >> SURROUNDED BY WALLS */
	// first line check ;
	while (s[0][i])
	{
		if (s[0][i] == '1' || s[0][i] == ' ')
			i++;
		else
			ft_errors(game, "Error.");
	}
	i = 0;
	// last line check;
	while (s[h][i])
	{
		if (s[h][i] == '1' || s[h][i] == ' ')
			i++;
		else
			ft_errors(game, "Error 3.");
	}
	i = -1;
	while (s[++i])
		check_last_element(game, s[i]);
}

char	**get_map(t_cub3D *game, t_map *map, int start)
{
	char	**map_1;
	char	**map_2;
	int		height;
	int		width;
	int		i;

	i = start;
	width = 0;
	height = 0;
	map_1 = map->file;
	skip_white_lines(map_1, &i);
	if (!map_1[i])
		ft_errors(game, "Error.");
	width = get_map_info(game, map_1, i, &height);
	map_2 = alloc_and_fill_map(game, &map_1[i], width, height);
	map->map = map_2;
	whole_map_check(game, map, (height - 1));
	return (map_2);
}

void	ft_check_map(t_cub3D *game, t_map *map, char *mapfile)
{
	int	start;

	map->fd = open(mapfile, O_RDONLY);
	if (map->fd < 0)
		ft_errors(game, "Error.");
	map->file = get_file_content(game, map->fd);
	start = get_basic_elements(game, map);
	map->map = get_map(game, map, start);
	print_map_info(map);
	game->map = map;
}

/* Map : Ends */

/* Main */

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
	return (game);
}

void    cub3D(t_cub3D *game)
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
	// cub3D(game);
	gc_free_all(game);
	return (0);
}
