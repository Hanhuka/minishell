/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:15:02 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/09/14 15:33:41 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include "../builtins.h"

int	ft_env(char ***env, int fd)
{
	int	i;

	if (fd < 2)
		return (1);
	i = 0;
	while (env[i] != 0 && ft_strchr(env[i], '=') != 0)
	{
		ft_putstr_fd(env[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	close(fd);
	return (1);
}
