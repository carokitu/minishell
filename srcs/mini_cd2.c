/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:06:30 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/22 12:39:12 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		mn_oldpwdstruct(t_mini *infos, int i)
{
	if (infos->pathon == 1)
	{
		free(infos->previous_path);
		infos->pathon = 0;
	}
	infos->previous_path = ft_strdup(infos->env[i] + 7);
	infos->pathon = 1;
}

void		mn_oldpwd(t_mini *infos)
{
	int		i;
	char	*buf;
	int		a;
	char	*tmp;
	char	*str;

	buf = NULL;
	i = 0;
	str = NULL;
	if ((i = mn_getline_env(infos, "OLDPWD=", 7)) == -1)
		i = mn_allouenv_2(infos);
	if (!(infos->envon == 1))
		mn_allouenv(infos);
	infos->envon = 1;
	tmp = infos->env[i];
	if ((a = mn_getline_env(infos, "PWD=", 4)) != -1)
		infos->env[i] = ft_strjoin("OLDPWD=", infos->env[a] + 4);
	else
	{
		str = getcwd(str, 100);
		infos->env[i] = ft_strjoin("OLDPWD=", str);
		free(str);
	}
	free(tmp);
	mn_oldpwdstruct(infos, i);
}

int			mn_allouenv_2(t_mini *infos)
{
	int		i;
	char	**save;
	char	*buf;

	buf = NULL;
	save = infos->env;
	i = 0;
	while (infos->env[i])
		i++;
	if (!(infos->env = (char **)malloc((sizeof(char *) * (i + 2)))))
		return (-1);
	i = 0;
	while (save[i])
	{
		infos->env[i] = ft_strdup(save[i]);
		i++;
	}
	mn_freesave(save, infos->envon);
	infos->env[i] = ft_strdup("OLDPWD=");
	infos->env[i + 1] = NULL;
	infos->envon = 1;
	return (i);
}

void		mn_allouenv_1(t_mini *infos)
{
	int		i;
	char	**save;
	char	*buf;

	buf = NULL;
	save = infos->env;
	i = 0;
	while (infos->env[i])
		i++;
	if (!(infos->env = (char **)malloc((sizeof(char *) * (i + 2)))))
		return ;
	i = 0;
	while (save[i])
	{
		infos->env[i] = ft_strdup(save[i]);
		i++;
	}
	mn_freesave(save, infos->envon);
	buf = getcwd(buf, 100);
	infos->env[i++] = ft_strjoin("PWD=", buf);
	free(buf);
	infos->envon = 1;
	infos->env[i] = NULL;
}

void		mn_allouenv(t_mini *infos)
{
	int		i;
	char	**save;

	if (infos->envon == 1)
		return ;
	save = infos->env;
	i = 0;
	while (infos->env[i])
		i++;
	if (!(infos->env = (char **)ft_memalloc((sizeof(char *)) * (i + 1))))
		return ;
	infos->envon = 1;
	i = 0;
	while (save[i])
	{
		infos->env[i] = ft_strdup(save[i]);
		i++;
	}
	infos->env[i] = NULL;
	return ;
}
