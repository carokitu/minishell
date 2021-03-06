/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 10:49:10 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/12 11:14:38 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		mn_start(t_mini *infos)
{
	int	i;
	int	res;

	i = 0;
	if (mn_getpath(infos) == 1)
		return (1);
	res = mn_read(infos);
	while (infos->path[i])
	{
		free(infos->path[i]);
		infos->path[i++] = NULL;
	}
	free(infos->path);
	if (infos->pathon == 1)
		free(infos->previous_path);
	mn_freesave(infos->env, infos->envon);
	free(infos);
	return (0);
}

int				main(int argc, char **argv, char **envp)
{
	t_mini *infos;

	if (argc == 0)
		return (1);
	argv[0] = NULL;
	if (!(infos = (t_mini *)malloc(sizeof(t_mini))))
		return (1);
	infos->tmp_env = NULL;
	infos->env = envp;
	infos->cmd = NULL;
	infos->flagson = 0;
	infos->pathon = 0;
	infos->gp_nbr = 0;
	infos->skipenv = -1;
	infos->envon = 0;
	infos->ipath = 0;
	infos->envon2 = 0;
	infos->unenv = 0;
	infos->exit = 0;
	return (mn_start(infos));
}
