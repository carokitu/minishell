/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cdnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:46:10 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/22 14:42:39 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		mn_newpwd(t_mini *infos)
{
	int		i;
	char	*buf;
	char	*str;

	buf = NULL;
	i = 0;
	if ((i = mn_getline_env(infos, "PWD=", 4)) == -1)
	{
		mn_allouenv_1(infos);
		return (-1);
	}
	if (!(infos->envon == 1))
		mn_allouenv(infos);
	str = getcwd(buf, 100);
	if (str != NULL)
	{
		free(infos->env[i]);
		infos->env[i] = ft_strjoin("PWD=", str);
	}
	free(str);
	free(buf);
	return (0);
}

int				mn_getline_env(t_mini *infos, char *str, int size)
{
	int i;

	i = 0;
	while (infos->env[i])
	{
		if (ft_strncmp(infos->env[i], str, size) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void		mn_cd_pathif(t_mini *infos)
{
	char	**tmp;
	int		res;

	res = 0;
	tmp = infos->flags;
	if (!(infos->flags = (char **)ft_memalloc(sizeof(char *) * 3)))
		return ;
	infos->flags[0] = ft_strdup(tmp[0]);
	if (infos->flags[1])
		free(infos->flags[1]);
	if (((res = mn_getline_env(infos, "HOME=", 5)) != -1))
		infos->flags[1] = ft_strdup(infos->env[res] + 5);
	else
		infos->flags[1] = ft_strdup("/Users/cde-moul");
	infos->flags[2] = NULL;
	mn_freesave(tmp, infos->flagson);
}

int				mn_cd_path(t_mini *infos)
{
	char		*path;

	if (mn_cderror(infos) == 1)
		return (1);
	if (!(infos->flags[1]) || ft_strlen(infos->flags[1]) == 0)
		mn_cd_pathif(infos);
	path = infos->flags[1];
	if (chdir(path) != 0)
	{
		mn_tirerror1(path);
		return (1);
	}
	mn_oldpwd(infos);
	mn_newpwd(infos);
	return (0);
}

int				mn_cd(t_mini *infos)
{
	int i;

	if (infos->flags[1] && ft_strcmp(infos->flags[1], "-") == 0)
	{
		if (infos->pathon == 0 &&
				((i = mn_getline_env(infos, "PWD=", 4)) == -1))
		{
			ft_putstr("/usr/bin/cd: line 4: cd: OLDPWD not set\n");
			if ((i = mn_getline_env(infos, "PWD=", 4)) == -1)
				mn_newpwd(infos);
			mn_oldpwd(infos);
			return (1);
		}
		else if (infos->pathon == 0)
			mn_oldpwd(infos);
		if (chdir(infos->previous_path) == -1)
		{
			mn_tirerror1(infos->previous_path);
			return (1);
		}
		mn_oldpwd(infos);
		mn_newpwd(infos);
		return (0);
	}
	return (mn_cd_path(infos));
}
