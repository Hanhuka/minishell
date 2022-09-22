/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:24:08 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/09/12 16:31:25 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include "../builtins.h"

int	parameters(char **args, int i);

int	ft_echo(char **args, int fd)
{
	int	i;
	int	n;

	if (fd < 2)
		return (1);
	i = 0;
	n = 0;
	while (args[i] != 0)
	{
		if (args[i][0] && args[i][0] == '-')
			if (parameters(args, i) == true)
				n = 1;
		else
			return (1);
	}
	i = 0;
	while (args[i] != 0)
	{
		if (args[i][0] && args[i][0] == '-')
			ft_putstr_fd(args[i], fd);
	}
	if (n == 0)
		ft_putchar_fd('\n', fd);
	return (0);
}

int	parameters(char **args, int i)
{
	if (args [i][1] && args[i][1] == 'n' && args[i][2] == 0 && args[i][2])
		return (true);
	else
		return (false);
}
