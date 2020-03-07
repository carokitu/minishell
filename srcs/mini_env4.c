/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 17:07:26 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/08 19:49:15 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		mn_getline(char **env, char *str, int size)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, size) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		mn_envbin(t_mini *infos, int *i)
{
	int		a;
	char	**arg;
	int		b;
	char	*barg;

	b = 0;
	a = *i;
	barg = NULL;
	while (infos->flags[a++])
		b++;
	if (!(arg = (char **)malloc(sizeof(char *) * (b + 1))))
		return (1);
	a = *i;
	b = 0;
	while (infos->flags[a])
		arg[b++] = ft_strdup(infos->flags[a++]);
	arg[b] = NULL;
	barg = ft_strdup(arg[0]);
	mn_envpath(infos, arg);
	mn_envbinaire(infos, arg, barg);
	mn_freesave(arg, 1);
	free(barg);
	return (1);
}

void	mn_tmpenv(t_mini *infos)
{
	mn_freesave(infos->tmp_env, 1);
	if (!(infos->tmp_env = (char **)malloc(sizeof(char *) * 1)))
		return ;
	infos->tmp_env[0] = NULL;
}

int		mn_eargenv(char *error)
{
	ft_putstr_fd("env: setenv ", STDOUT_FILENO);
	ft_putstr_fd(error, STDOUT_FILENO);
	ft_putstr_fd(": Invalid argument\n", STDOUT_FILENO);
	return (1);
}
