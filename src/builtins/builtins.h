/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:57:27 by pcoimbra          #+#    #+#             */
/*   Updated: 2022/09/14 16:03:50 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../minishell.h"

// builtins

int	ft_echo(char **args, int fd);
int	ft_exit(char **args, int *stat, int fd);
int	ft_env(char ***env, int fd);
int	ft_pwd(int fd);

#endif
