/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:30:16 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/09/14 16:00:58 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include "../builtins.h"

static void	param_err(char **args);

int	ft_exit(char **args, int *stat, int fd)
{
	if (fd < 2)
		return (1);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (rgs[1] == 0)
		exit(*stat);
	param_err(args);
	if (rgs[1] != 0 && args[2] != 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		*stat = 1;
		return (1);
	}
	(*stat) = ft_atoi(args[1]);
	free(args[1]);
	exit(*stat);
}

static void	param_err(char **args)
{
	int	i;

	i = 0;
	while (args[1][i] == '\t')
		i++;
	while (args[1][i] == '+' || args[1][i] == '-')
		i++;
	while (args[1][i] != '\0')
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit(255);
		}
		i++;
	}
}
