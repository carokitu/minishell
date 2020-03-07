/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:07:05 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/15 12:59:54 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			mn_printenv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i]);
		ft_putchar('\n');
		i++;
	}
	return (0);
}

static int	mn_envhelp(void)
{
	ft_putstr("env: option requires an argument -- u");
	ft_putstr("\nusage: env [-iv]");
	ft_putstr("[-u name]\n");
	ft_putstr("\t[name=value ...]\n");
	return (1);
}

static int	mn_unenv(t_mini *infos, int *i, char **env)
{
	char	*str;
	int		a;

	a = 0;
	while (infos->flags[*i][a])
	{
		if (infos->flags[*i][a] == '=')
		{
			ft_putstr("env: unsetenv ");
			ft_putstr(infos->flags[*i]);
			ft_putstr(": Invalid argument\n");
			return (1);
		}
		a++;
	}
	str = ft_strjoin(infos->flags[*i], "=");
	if (infos->tmp_env[0] != NULL)
		a = mn_getline(env, str, ft_strlen(str));
	else
		a = -1;
	mn_getnewenv(infos, a);
	free(str);
	return (0);
}

static int	mn_getargienv(t_mini *infos, int *i, char **env)
{
	int	a;

	a = 0;
	if (mn_checkenv1(infos->flags[*i]) == 1)
		return (1);
	while (infos->flags[*i][++a])
	{
		if (infos->flags[*i][a] == 'u')
		{
			if (!(infos->flags[(*i) + 1]))
				return (mn_envhelp());
			else
			{
				(*i)++;
				if (mn_unenv(infos, i, env) == -1)
					return (1);
			}
		}
		else if (infos->flags[*i][a] == 'i')
			mn_tmpenv(infos);
	}
	return (0);
}

int			mn_env(t_mini *infos)
{
	int		i;
	int		res;

	res = 0;
	i = 0;
	infos->tmp_env = mn_dupstr(infos->env);
	while (infos->flags[++i] && res == 0)
	{
		if (infos->flags[i][0] == '-')
			res = mn_getargienv(infos, &i, infos->tmp_env);
		else if (infos->flags[i][0] == '=')
			res = mn_eargenv(infos->flags[i]);
		else if (ft_strcmp(infos->flags[i], "env") != 0)
		{
			if (mn_envadd(infos->flags[i]) == 1)
				res = mn_addenv(infos, infos->flags[i]);
			else
				res = mn_envbin(infos, &i);
		}
	}
	if (res == 0)
		mn_printenv(infos->tmp_env);
	mn_freesave(infos->tmp_env, 1);
	return (0);
}
