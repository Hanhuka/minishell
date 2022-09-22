/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:36:05 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/22 18:34:43 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_diff_s(char *str, int i, char *test)
{
	int	i2;

	i2 = 0;
	while (str[i] && test[i2] && !((i < 1 || str[i - 1] != '\\')
			&& str[i] == test[i2]))
		i2++;
	if (!test[i2])
		return (1);
	return (0);
}

int	skip_quotes(char *str, int i)
{
	char	q;

	q = str[i];
	i++;
	while (str[i] && !((i < 1 || str[i - 1] != '\\') && str[i] == q))
		i++;
	if (!str[i])
	{
		printf("skip quotes syntax\n");
		syntax_error();
	}
	return (i);
}

int	count_quotes(char *str)
{
	int		i;
	int		count;
	char	qt;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && !is_diff_s(str, i, "\"'"))
		{
			qt = str[i];
			i++;
			while (str[i] && !((i < 1 || str[i - 1] != '\\') && str[i] == qt))
				i++;
			count += 2;
		}
		i++;
	}
	return (count);
}

char	*remove_quotes_util(char *str, int i, int i2, char qt)
{
	char	*newstr;

	newstr = malloc(sizeof(char) * ft_strlen(str) - count_quotes(str) + 1);
	while (str[i])
	{
		if (str[i] && !is_diff_s(str, i, "\"'"))
		{
			qt = str[i];
			i++;
			while (str[i] && !((i < 1 || str[i - 1] != '\\') && str[i] == qt))
			{
				newstr[i2] = str[i];
				i2++;
				i++;
			}
		}
		else
		{
			newstr[i2] = str[i];
			i2++;
		}
		i++;
	}
	newstr[i2] = 0;
	return (newstr);
}

char	*remove_quotes(char *str)
{
	char	*newstr;
	char	*newstr2;

	newstr = remove_quotes_util(str, 0, 0, 'a');
	free(str);
	newstr2 = rm_backslash(newstr, 0, 0, 'a');
	return (newstr2);
}
