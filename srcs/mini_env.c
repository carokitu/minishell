/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 12:57:01 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/23 16:02:58 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	mn_flagenv(char *line, t_mini *infos)
{
	int	i;

	infos->skipenv = -1;
	i = -1;
	while (infos->env[++i])
	{
		if (ft_strncmp(line, infos->env[i], ft_strlen(line)) == 0)
		{
			infos->skipenv = i;
			return (0);
		}
	}
	return (1);
}

static int	mn_envhelp(char arg)
{
	ft_putstr("env: illegal option -- ");
	ft_putchar(arg);
	ft_putstr("\nusage: env [-iv]");
	ft_putstr("[-u name]\n");
	ft_putstr("\t[name=value ...]\n");
	return (2);
}

static int	mn_checkenv2(t_mini *infos)
{
	if (infos->flags[1][0] != '-')
	{
		if (mn_setenv(infos) == 1)
		{
			ft_putstr("env: ");
			ft_putstr(infos->flags[1]);
			ft_putstr(": No such file or directory\n");
			return (1);
		}
		return (0);
	}
	return (2);
}

static int	mn_checkenv1(t_mini *infos)
{
	if (ft_strcmp(infos->flags[1], "-v") == 0)
	{
		if (infos->flags[2] && !(infos->flags[3])
			&& mn_flagenv(infos->flags[2], infos) == 1)
		{
			printf("if\n");
			return (1);
		}
		return (0);
	}
	if (ft_strcmp(infos->flags[1], "-u") == 0)
	{
		printf("TO UNSET \n");
		return (2);
	}
	if (ft_strcmp(infos->flags[1], "--help") == 0
			|| ((infos->flags[1][0] == '-') && infos->flags[1][1]))
		return (mn_envhelp(infos->flags[1][1]));
	return (mn_checkenv2(infos));
}

int			mn_checkenv(t_mini *infos)
{
	if (!(infos->flags[1]))
		return (0);
	if (ft_strcmp(infos->flags[1], "-i") == 0
			|| ft_strcmp(infos->flags[1], "-") == 0
			|| ft_strcmp(infos->flags[1], "ignore-environment") == 0)
	{
		if (infos->flags[2])
		{
			ft_putstr("env: ");
			ft_putstr(infos->flags[1]);
			ft_putstr(": Too many arguments to function called\n");
		}
		return (2);
	}
	return (mn_checkenv1(infos));
}
