/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_checkdolls2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 11:48:44 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/22 14:42:41 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		mn_isok(char *str, int i)
{
	if (str[i] &&
		((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
		|| (str[i] >= '0' && str[i] <= '9') || (str[i] == '_')))
		return (0);
	return (1);
}

static char		*mn_printerror(char **env, char **ctn, t_mini *infos,
		char **flag)
{
	ft_putstr(*ctn);
	ft_putstr(": Undefined variable.\n");
	free(*ctn);
	free(*flag);
	free(*env);
	infos->skipenv = 1;
	return (ft_strdup("error"));
}

static char		*mn_fill_new(char *flag, t_mini *infos, int i)
{
	int		start;
	int		a;
	char	*env;
	char	*ctn;

	start = i++;
	while (mn_isok(flag, i) == 0)
		i++;
	ctn = ft_strsub(flag, start + 1, i - (start + 1));
	env = ft_strjoin(ctn, "=");
	if ((a = mn_getline_env(infos, env, ft_strlen(env))) == -1)
		return (mn_printerror(&env, &ctn, infos, &flag));
	free(ctn);
	ctn = ft_strdup(infos->env[a] + ft_strlen(env));
	if (ft_strlen(ctn) == 0)
	{
		mn_freethree(&env, &ctn, &flag);
		return (ft_strdup(""));
	}
	free(env);
	return (mn_dolls2(&flag, i, start, &ctn));
}

static char		*mn_dolls(char *flag, t_mini *infos)
{
	int		i;
	char	*new;

	new = NULL;
	i = 0;
	while (flag[i])
	{
		if (flag[i] == '$' && (flag[i + 1] &&
					flag[i + 1] != '\t' && flag[i + 1] != '\n'
				&& flag[i + 1] != ' ' && flag[i + 1] != '$'))
		{
			flag = mn_fill_new(flag, infos, i);
			if (ft_strlen(flag) == 0)
				return (flag);
		}
		if (flag[i] == '$' && flag[i + 1] && flag[i + 1] == '$')
			i++;
		i++;
	}
	return (flag);
}

int				mn_checkdolls(t_mini *infos)
{
	int		i;

	i = 0;
	while (infos->flags[i])
	{
		infos->flags[i] = mn_dolls(infos->flags[i], infos);
		if (infos->skipenv == 1)
		{
			infos->skipenv = 0;
			return (1);
		}
		i++;
	}
	return (0);
}
