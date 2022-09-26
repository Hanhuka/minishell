/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_dollar3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:55:36 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/26 18:15:08 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_status_utils(char *str, int i, char *val, char **newstr)
{
	int		i2;
	int		ii;
	int		i3;

	i3 = 0;
	i2 = 0;
	ii = 0;
	while (str[i2 + i3])
	{
		if ((i2 + ii) == i)
		{
			while (val[ii])
			{
				(*newstr)[i2 + ii] = val[ii];
				ii++;
			}
			i3 = 2;
		}
		else
		{
			(*newstr)[i2 + ii] = str[i2 + i3];
			i2++;
		}
	}
	(*newstr)[i2 + ii] = 0;
}
