/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:51:08 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/15 15:49:47 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	mn_setenvv2(t_mini *infos, int a, char **save)
{
	int		i;
	char	*tmp;
	int		b;

	b = 0;
	i = 0;
	tmp = NULL;
	while (save[i])
	{
		mn_setenv2bis(infos, i, &a, save);
		i++;
	}
	if (a != -1)
	{
		tmp = ft_strjoin(infos->flags[1], "=");
		if (infos->flags[2])
			infos->env[i++] = ft_strjoin(tmp, infos->flags[2]);
		else
			infos->env[i++] = ft_strdup(tmp);
		free(tmp);
	}
	infos->env[i] = NULL;
	mn_freesave(save, infos->envon2);
	mn_getpath(infos);
	return (0);
}

static int	mn_setenvv(t_mini *infos, int a)
{
	int		i;
	char	**save;

	save = infos->env;
	i = 0;
	if (mn_setenverror(infos) == 1)
		return (1);
	while (infos->env[i])
		i++;
	i++;
	if (infos->envon == 1)
		infos->envon2 = 1;
	if (!(infos->env = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
	{
		ft_putstr_fd("env: Insufficient memory to add a ", STDOUT_FILENO);
		ft_putstr_fd("new variable to the environment\n", STDOUT_FILENO);
		return (1);
	}
	infos->envon = 1;
	return (mn_setenvv2(infos, a, save));
}

static int	mn_checkusage(t_mini *infos)
{
	if (infos->flags[1] && infos->flags[2] && infos->flags[3])
	{
		ft_putstr_fd("setenv: Too many arguments.\n",
				STDOUT_FILENO);
		return (1);
	}
	return (0);
}

static int	mn_sett(t_mini *infos, char *name, int *i)
{
	while (infos->env[++(*i)])
	{
		if (ft_strncmp(infos->env[*i], name, ft_strlen(name)) == 0)
		{
			free(name);
			return (mn_setenvv(infos, *i));
		}
	}
	free(name);
	return (2);
}

int			mn_setenvarg(t_mini *infos)
{
	int		i;
	char	*name;
	char	*value;
	int		a;

	a = 0;
	name = NULL;
	value = NULL;
	i = -1;
	if (mn_checkusage(infos) == 1)
		return (1);
	if (infos->flags[1])
		name = ft_strjoin(infos->flags[1], "=");
	else
		return (mn_printenv(infos->env));
	if (infos->flags[2])
		value = infos->flags[2];
	else
		value = NULL;
	if ((a = mn_sett(infos, name, &i)) != 2)
		return (a);
	return (mn_setenvv(infos, i));
}
