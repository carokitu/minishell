/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_treat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:48:05 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/22 13:39:21 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		mn_binary(t_mini *infos)
{
	int	i;

	i = -1;
	ft_putstr("binaire : ");
	ft_putstr(infos->cmd);
	ft_putstr("\n");
	while (infos->flags[++i])
	{
		ft_putstr("infos->flags ");
		ft_putnbr(i);
		ft_putstr(" : ");
		ft_putnbr(i);
		ft_putstr(infos->flags[i]);
		ft_putstr("\n");
	}
}

static int	mn_infct(t_mini *infos, int i)
{
	int	(*fonction[5])(t_mini *infos);

	fonction[0] = mn_echo;
	fonction[1] = mn_cd;
	fonction[2] = mn_setenv;
	fonction[3] = mn_unsetenv;
	fonction[4] = mn_env;
	return (fonction[i](infos));
}

static int	mn_builtins(t_mini *infos)
{
	int	i;

	i = ft_chrpos(FIRST_LETTERS, infos->cmd[0]);
	if (i == -1)
		return (1);
	else if (i == 0)
	{
		if (infos->cmd[1] == 'c')
			i = 0;
		else if (infos->cmd[1] == 'n')
			i = 4;
		else
			return (1);
	}
	return (mn_infct(infos, i));
}

int			mn_treat(t_mini *infos, char *line)
{
	int	res;

	res = 0;
	if (mn_getarg(infos, line) == 1)
		return (1);
	res = mn_checkarg(infos);
	if (res != 0)
		return (res);
	if (infos->cmd[0] == '/')
		mn_binary(infos);
	else
		return (mn_builtins(infos));
	return (0);
}
