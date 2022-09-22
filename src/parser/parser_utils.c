/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:46:02 by ralves-g          #+#    #+#             */
/*   Updated: 2022/09/22 16:07:04 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && !is_diff_s(str, i, "|"))
		syntax_error();
	while (str[i])
	{
		if (str[i] && !is_diff_s(str, i, "\"'"))
			i = skip_quotes(str, i);
		if (str[i] && !is_diff_s(str, i, "|"))
		{
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if (str[i] && !is_diff_s(str, i, "|"))
				syntax_error();
		}
		else
			i++;
	}
}
