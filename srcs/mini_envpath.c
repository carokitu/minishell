/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_checkarg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:18:43 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/15 12:22:23 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	mn_changecmd(char **arg, char *path, DIR *dir)
{
	char	*tmp;
	char	*tmp2;

	closedir(dir);
	tmp = arg[0];
	if ((arg[0] = ft_strjoin(path, "/")) == NULL)
		return (1);
	tmp2 = arg[0];
	if ((arg[0] = ft_strjoin(tmp2, tmp)) == NULL)
		return (1);
	free(tmp);
	free(tmp2);
	return (0);
}

static int	mn_checkbin(t_mini *infos, char **arg)
{
	DIR				*dir;
	struct dirent	*inf;
	int				i;

	i = 0;
	while (infos->path[i] != NULL)
	{
		if ((dir = opendir(infos->path[i])) != NULL)
		{
			while ((inf = readdir(dir)) != NULL)
			{
				if (ft_strcmp(inf->d_name, arg[0]) == 0)
					return (mn_changecmd(arg, infos->path[i], dir));
			}
			closedir(dir);
		}
		i++;
	}
	return (1);
}

int			mn_envpath(t_mini *infos, char **arg)
{
	if (arg[0][0] == '/')
		return (0);
	return (mn_checkbin(infos, arg));
}

static int	mn_addenv2(t_mini *infos, char *arg)
{
	int		i;
	char	**tmp;
	char	**new;

	tmp = infos->tmp_env;
	i = 0;
	while (tmp[i])
		i++;
	if (!(new = (char **)malloc(sizeof(char *) * (i + 2))))
		return (1);
	i = -1;
	while (tmp[++i])
		new[i] = ft_strdup(tmp[i]);
	new[i] = ft_strdup(arg);
	new[i + 1] = NULL;
	mn_freesave(tmp, 1);
	infos->tmp_env = new;
	return (0);
}

int			mn_addenv(t_mini *infos, char *arg)
{
	int		a;
	char	*str;

	a = 0;
	while (arg[a] != '=')
		a++;
	str = ft_strsub(arg, 0, a + 1);
	a = mn_getline(infos->tmp_env, str, ft_strlen(str));
	free(str);
	if (a != -1)
	{
		free(infos->tmp_env[a]);
		infos->tmp_env[a] = ft_strdup(arg);
	}
	else
		return (mn_addenv2(infos, arg));
	return (0);
}
