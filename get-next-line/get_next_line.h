/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 08:40:57 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/14 18:20:25 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

size_t	ft_strlen_1(const char *str);
void	*ft_memcpy_1(void *dest, const void *src, size_t n);
char	*ft_strjoin_1(char const *s1, char const *s2);
int		ft_strchr_1(const char *str, int c);

#endif