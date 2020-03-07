/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 13:13:54 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/23 13:07:31 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	mn_exec(t_mini *infos)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		exit(execve(infos->flags[0], infos->flags, infos->env));
	if (pid > 0)
		wait(&pid);
	if (pid < 0)
		return (1);
	return (0);
}

static int	mn_isntfile(t_mini *infos)
{
	ft_putstr_fd(infos->flags[0], STDOUT_FILENO);
	ft_putstr_fd(": Permission denied.\n", STDOUT_FILENO);
	return (0);
}

static int	mn_noaccess(t_mini *infos)
{
	ft_putstr_fd(infos->flags[0], STDOUT_FILENO);
	ft_putstr_fd(": Command not found.\n", STDOUT_FILENO);
	return (0);
}

int			mn_treatbinary(t_mini *infos)
{
	struct stat		*sts;

	if (!(sts = (struct stat *)malloc(sizeof(struct stat))))
		return (1);
	if (lstat(infos->flags[0], sts) == -1)
	{
		free(sts);
		return (mn_noaccess(infos));
	}
	else if (!(sts->st_mode & S_IXUSR))
	{
		ft_putstr_fd("./minishell: permission denied: ", STDOUT_FILENO);
		ft_putstr_fd(infos->flags[0], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(sts);
		return (0);
	}
	else if (!(S_ISREG(sts->st_mode)))
	{
		free(sts);
		return (mn_isntfile(infos));
	}
	free(sts);
	return (mn_exec(infos));
}
