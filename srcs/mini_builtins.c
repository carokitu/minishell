/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 12:26:34 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/23 16:23:08 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mn_putdolls(char *ligne, t_mini *infos)
{
	int	i;

	i = -1;
	while (infos->env[++i])
	{
		if (ft_strncmp(infos->env[i], ligne + 1, (ft_strlen(ligne) - 1)) == 0)
		{
			ft_putstr(infos->env[i] + (ft_strlen(ligne)));
			return ;
		}
	}
	ft_putstr(ligne);
}

int		mn_echo(t_mini *infos)
{
	int	i;
	int ret;

	ret = 1;
	i = 0;
	if (infos->flags[1] && ft_strcmp(infos->flags[1], "-n") == 0)
	{
		ret = 0;
		i++;
	}
	while (infos->flags[++i])
	{
		if (i != 1 && !(i == 2 && ret == 0))
			ft_putchar(' ');
		if (infos->flags[i][0] == '$')
			mn_putdolls(infos->flags[i], infos);
		else
			ft_putstr(infos->flags[i]);
	}
	if (ret == 1)
		ft_putchar('\n');
	return (0);
}

int		mn_setenv(t_mini *infos)
{
	int res;

	res = 0;
	printf("SETENV : infos->cmd : %s\n", infos->cmd);
	res = mn_setenvarg(infos);
	if (res == 1)
		return (1);
	if (res == 2)
		return (0);
// TRAITER LES BON CAS AVEC FORK ET EXECVE <3
	return (0);
}

int		mn_unsetenv(t_mini *infos)
{
	printf("infos->cmd : %s\n", infos->cmd);	
	return (0);
}

int		mn_env(t_mini *infos)
{
	int res;
	int	i;

	i = 0;
	res = mn_checkenv(infos);
	if (res == 1)
		return (1);
	if (res == 2)
		return (0);
	while (infos->env[++i])
	{
		if (i != infos->skipenv)
		{
			ft_putstr(infos->env[i]);
			ft_putchar('\n');
		}
	}
	infos->skipenv = -1;
	return (0);
}
