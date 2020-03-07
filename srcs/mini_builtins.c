/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 12:26:34 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/22 14:00:31 by cde-moul         ###   ########.fr       */
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
	res = mn_setenvarg(infos);
	if (res == 1)
		return (1);
	return (0);
}

int		mn_unsetenv(t_mini *infos)
{
	int i;

	i = -1;
	if (infos->flags[2])
	{
		ft_putstr_fd("unsetenv: usage: [NAME]\n", STDOUT_FILENO);
		return (1);
	}
	while (infos->flags[1][++i])
	{
		if (infos->flags[1][i] == '=')
		{
			ft_putstr_fd("unsetenv: name must not contain '=' character\n",
					STDOUT_FILENO);
			return (1);
		}
	}
	return (mn_unsetenv2(infos));
}
