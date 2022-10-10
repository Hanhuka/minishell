/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:13:04 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/07 20:13:19 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	no_args(char **env)
{
	int	y;

	y = 0;
	while (env[y])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[y], 1);
		ft_putstr_fd("\n", 1);
		y++;
	}
	return (1);
}
