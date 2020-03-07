/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:13:54 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/08 19:42:43 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	mn_exec(t_mini *infos, char **arg)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		exit(execve(arg[0], arg, infos->tmp_env));
	if (pid > 0)
		wait(&pid);
	if (pid < 0)
		return (1);
	return (0);
}

static int	mn_noaccess(char *arg)
{
	ft_putstr_fd("env: ", STDOUT_FILENO);
	ft_putstr_fd(arg, STDOUT_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
	return (0);
}

int			mn_envbinaire(t_mini *infos, char **arg, char *barg)
{
	struct stat		*sts;

	if (!(sts = (struct stat *)malloc(sizeof(struct stat))))
		return (1);
	if (lstat(arg[0], sts) == -1)
	{
		free(sts);
		return (mn_noaccess(arg[0]));
	}
	else if (!(sts->st_mode & S_IXUSR) || !(S_ISREG(sts->st_mode)))
	{
		ft_putstr_fd("en: ", STDOUT_FILENO);
		ft_putstr_fd(barg, STDOUT_FILENO);
		ft_putstr_fd(": Permission denied\n", STDOUT_FILENO);
		free(sts);
		return (0);
	}
	free(sts);
	return (mn_exec(infos, arg));
}

int			mn_envadd(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
