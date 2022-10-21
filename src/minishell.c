/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:25:48 by ralves-g          #+#    #+#             */
/*   Updated: 2022/10/07 20:10:45 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_status = 0;

int	main(int ac, char **av, char **env)
{
	t_tree	*tree;
	char	*line;
	char	**env2;

	(void)ac;
	(void)av;
	*synt() = 0;
	tree = NULL;
	env2 = get_env(env);
	ignore_slashl();
	while (1)
	{
		call_sigact(SI_RLINE);
		line = readline("\e[1;32mralves-g&pcoimbra:\e[1;34mshell> \e[0m");
		// line = readline("ralves-g&pcoimbra:shell> ");
		call_sigact(SI_IGN);
		if (line && ft_strlen(line))
			add_history(line);
		if (!line)
		{
			printf("\nexit\n");
			rl_clear_history();
			exit(0);
		}
		if (!ft_strlen(line))
		{
			free(line);
			continue ;
		}
		parser(line, &tree, 0, env2);
		if (!(*synt()))
			execute_tree(&tree, &env2);
		free_tree(free_tree_utils(&tree));
		*synt() = 0;
	}
}
