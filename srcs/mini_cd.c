/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 14:21:07 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/23 15:43:13 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		mn_error_cd(t_mini *infos)
{
	struct stat *in;

	if (!(in = (struct stat *)malloc(sizeof(struct stat))))
		return (1);
	if (lstat(infos->flags[1], in) == -1)
		mn_error_cd1(infos->flags[1]);
	else
		mn_error_cd2(infos->flags[1], in);
	free(in);
	return (1);
}

static void		mn_cd_home(t_mini *infos)
{
	int i;

	if (ft_strcmp(infos->flags[1], "~") == 0
			|| ft_strcmp(infos->flags[1], "--") == 0)
	{
		free(infos->flags[1]);
		infos->flags[1] = ft_strdup("/Users/cde-moul");
		i = -1;
		while (infos->env[++i])
		{
			if (ft_strncmp(infos->env[i], "HOME=", 5) == 0)
			{
				free(infos->flags[1]);
				infos->flags[1] = ft_strdup(infos->env[i] + 5);
			}
		}
	}
	return ;
}

static int		mn_cd_path(t_mini *infos, char *current)
{
	char	*path;

	if (!(infos->flags[1]))
	{
		free(current);
		return (1);
	}
	mn_cd_home(infos);
	path = infos->flags[1];
	if (chdir(path) != 0)
	{
		free(current);
		return (mn_error_cd(infos));
	}
	else
	{
		if (infos->pathon != 0)
			free(infos->previous_path);
		infos->previous_path = current;
		infos->pathon = 1;
	}
	return (0);
}

int				mn_cd(t_mini *infos)
{
	char	*current;

	current = NULL;
	current = getcwd(current, 100);
	if (infos->flags[1] && ft_strcmp(infos->flags[1], "-") == 0)
	{
		if (infos->pathon == 0)
		{
			ft_putstr(current);
			infos->previous_path = current;
			infos->pathon = 1;
		}
		else
		{
			if (chdir(infos->previous_path) == -1)
				return (1);
			ft_putstr(infos->previous_path);
			free(infos->previous_path);
			infos->previous_path = current;
		}
		ft_putchar('\n');
	}
	else
		return (mn_cd_path(infos, current));
	return (0);
}
