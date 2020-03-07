/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_treat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 16:46:58 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/22 14:40:03 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		mn_binary(t_mini *infos)
{
	mn_treatbinary(infos);
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

int			mn_treat(t_mini *infos, char **line, char **save)
{
	int	res;

	res = 0;
	mn_checksep(line, save);
	if (mn_getarg(infos, *line) == 1 || mn_checkdolls(infos) == 1)
		return (1);
	mn_checkflags(infos);
	res = mn_checkarg(infos);
	if (res != 0)
		return (res);
	if (infos->cmd[0] == '/' || infos->cmd[0] == '.')
		mn_binary(infos);
	else
		return (mn_builtins(infos));
	return (0);
}
