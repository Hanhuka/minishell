/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:48:14 by ralves-g          #+#    #+#             */
/*   Updated: 2022/08/03 14:48:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *str, int start, int end)
{
	char	*sub;
	int		i;

	i = 0;
	if (start > end)
		return (NULL);
	sub = malloc(end - start + 2);
	while (start <= end)
	{
		sub[i] = str[start];
		start++;
		i++;
	}
	sub[i] = 0;
	return (sub);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i])
		i++;
	ptr = malloc(i + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

int	is_dif(char c, char *chars)
{
	int i;

	i = 0;
	while (chars[i] && chars[i] != c)
		i++;
	if (!chars[i])
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while (i < n - 1 && *(s1 + i) == *(s2 + i)
		&& *(s1 + i) != '\0' && *(s2 + i) != '\0')
		i++;
	return ((*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i)));
}
