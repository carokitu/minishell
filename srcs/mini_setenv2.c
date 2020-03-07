/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_setenv2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 12:15:42 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/15 15:54:57 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		mn_setenv2bis(t_mini *infos, int i, int *a, char **save)
{
	char *tmp;

	tmp = NULL;
	if (i == *a)
	{
		infos->env[i] = NULL;
		tmp = ft_strjoin(infos->flags[1], "=");
		if (infos->flags[2])
			infos->env[i] = ft_strjoin(tmp, infos->flags[2]);
		else
			infos->env[i] = ft_strdup(tmp);
		free(tmp);
		*a = -1;
	}
	else
		infos->env[i] = ft_strdup(save[i]);
}

int			mn_setenverror(t_mini *infos)
{
	int	i;

	i = 0;
	if ((!(infos->flags[1][i] >= 'a' && infos->flags[1][i] <= 'z'))
		&& (!(infos->flags[1][i] >= 'A' && infos->flags[1][i] <= 'Z')))
	{
		ft_putstr_fd("setenv: Variable name must begin with a letter.\n",
				STDOUT_FILENO);
		return (1);
	}
	i++;
	while (infos->flags[1][i])
	{
		if ((!(infos->flags[1][i] >= 'a' && infos->flags[1][i] <= 'z'))
		&& (!(infos->flags[1][i] >= 'A' && infos->flags[1][i] <= 'Z'))
		&& (!(infos->flags[1][i] >= '0' && infos->flags[1][i] <= '9'))
		&& (!(infos->flags[1][i] == '_')))
		{
			ft_putstr_fd("setenv: Variable name must contain", STDOUT_FILENO);
			ft_putstr_fd(" alphanumeric characters.\n", STDOUT_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}
