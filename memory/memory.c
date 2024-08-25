/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:57:02 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/19 14:38:51 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
	gc_add(game, split);
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
