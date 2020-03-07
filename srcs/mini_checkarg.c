/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_checkarg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:18:43 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/22 14:01:13 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	mn_changecmd(t_mini *infos, char *path, DIR *dir)
{
	char	*tmp;
	char	*tmp2;

	closedir(dir);
	tmp = infos->cmd;
	if ((infos->cmd = ft_strjoin(path, "/")) == NULL)
		return (1);
	tmp2 = infos->cmd;
	if ((infos->cmd = ft_strjoin(tmp2, tmp)) == NULL)
		return (1);
	free(tmp);
	free(tmp2);
	tmp = infos->flags[0];
	if ((infos->flags[0] = ft_strjoin(path, "/")) == NULL)
		return (1);
	tmp2 = infos->flags[0];
	if ((infos->flags[0] = ft_strjoin(tmp2, tmp)) == NULL)
		return (1);
	free(tmp);
	free(tmp2);
	return (0);
}

static void	mn_printerror(char *error)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(": Command not found.\n", STDERR_FILENO);
}

static int	mn_checkbin(t_mini *infos)
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
				if (ft_strcmp(inf->d_name, infos->cmd) == 0)
					return (mn_changecmd(infos, infos->path[i], dir));
			}
			closedir(dir);
		}
		i++;
	}
	if (mn_isexc(infos) == 0)
		return (0);
	mn_printerror(infos->flags[0]);
	return (1);
}

static int	mn_checkcmd(t_mini *infos)
{
	if (infos->cmd[0] == '/')
		return (0);
	return (mn_checkbin(infos));
}

int			mn_checkarg(t_mini *infos)
{
	char	*fonction[5];
	int		i;

	fonction[0] = "echo";
	fonction[1] = "cd";
	fonction[2] = "setenv";
	fonction[3] = "unsetenv";
	fonction[4] = "env";
	i = -1;
	while (++i <= 4)
	{
		if (ft_strcmp(infos->cmd, fonction[i]) == 0)
			return (0);
	}
	if (ft_strcmp(infos->cmd, "exit") == 0 && !(infos->flags[1]))
	{
		infos->exit = 1;
		return (0);
	}
	else if (ft_strcmp(infos->cmd, "exit") == 0)
	{
		ft_putstr_fd("exit: Expression Syntax.\n", STDOUT_FILENO);
		return (0);
	}
	return (mn_checkcmd(infos));
}
