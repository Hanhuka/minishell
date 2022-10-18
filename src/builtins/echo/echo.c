/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:24:08 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/10/14 12:01:23 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_echo(char **args, int fd)
{
	int	y;

	y = 1;
	if (matrix_size(args) > 1 && !ft_strncmp(args[1], "-n",
			ft_strlen(args[1])))
		y++;
	while (args[y])
	{
		ft_putstr_fd(args[y], fd);
		if (args[y + 1])
			ft_putstr_fd(" ", fd);
		y++;
	}
	if (!(matrix_size(args) > 1 && !ft_strncmp(args[1], "-n",
				ft_strlen(args[1]))))
		ft_putstr_fd("\n", fd);
	free_matrix(args);
	g_status = 0;
	return (1);
}
