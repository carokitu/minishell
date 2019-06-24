/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_get_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:22:04 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/21 11:09:41 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		mn_getpath2(t_mini *infos, int ok, int a)
{
	int i;
	int	nbr;

	nbr = 0;
	i = 5;
	if (!(infos->path = (char **)ft_memalloc(sizeof(char *) * (ok + 1))))
		return (1);
	if (ok == 0)
	{
		infos->path[0] = NULL;
		return (0);
	}
	while (infos->env[a][i])
	{
		ok = i;
		if (infos->env[a][i] != '/')
			return (0);
		while (infos->env[a][i] && infos->env[a][i] != ':')
			i++;
		if ((infos->env[a][i] == ':' || !(infos->env[a][i]))
				&& infos->env[a][i] != '\n')
			infos->path[nbr++] = ft_strsub(infos->env[a], ok, i++ - ok);
	}
	infos->path[nbr] = NULL;
	return (0);
}

int				mn_getpath(t_mini *infos)
{
	int i;
	int	a;
	int	ok;

	ok = 0;
	a = 0;
	i = -1;
	while (infos->env[a] && (ok == 0))
	{
		if (ft_strncmp(infos->env[a], "PATH=", 5) == 0)
			ok = 1;
		else
			a++;
	}
	while (infos->env[a] && infos->env[a][++i])
	{
		if (infos->env[a][i] == ':')
			ok++;
	}
	return (mn_getpath2(infos, ok, a));
}
