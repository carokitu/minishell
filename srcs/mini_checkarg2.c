/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_chekarg2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:41:08 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/18 23:07:56 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		mn_allouehome(t_mini *infos)
{
	int		i;
	char	**save;

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
	infos->env[i] = ft_strdup("HOME=/Users/cde-moul");
	infos->env[i + 1] = NULL;
	infos->envon = 1;
	return (i);
}

static void		mn_gethome(t_mini *infos, int i)
{
	int		res;
	char	*str;

	str = NULL;
	res = 0;
	if (!(infos->flags[i][1]))
		res = 1;
	else if (infos->flags[i][1] == '/')
		str = ft_strsub(infos->flags[i], 1, ft_strlen(infos->flags[i]));
	else
		return ;
	free(infos->flags[i]);
	if (((res = mn_getline_env(infos, "HOME=", 5)) != -1) && str != NULL)
	{
		infos->flags[i] = ft_strjoin(infos->env[res] + 5, str);
		free(str);
	}
	else if (str == NULL && res != -1)
		infos->flags[i] = ft_strdup(infos->env[res] + 5);
	else
	{
		res = mn_allouehome(infos);
		infos->flags[i] = ft_strdup(infos->env[res] + 5);
	}
}

void			mn_checkflags(t_mini *infos)
{
	int i;

	i = 0;
	while (infos->flags[++i])
	{
		if (infos->flags[i][0] == '~')
			mn_gethome(infos, i);
	}
}

int				mn_isexc(t_mini *infos)
{
	struct stat		*sts;

	if (infos->cmd[0] != '.' || infos->cmd[1] != '/')
		return (1);
	if (!(sts = (struct stat *)malloc(sizeof(struct stat))))
		return (1);
	if (lstat(infos->cmd, sts) == -1)
	{
		free(sts);
		return (1);
	}
	if (sts->st_mode & S_IXUSR)
	{
		free(sts);
		return (0);
	}
	free(sts);
	return (0);
}
