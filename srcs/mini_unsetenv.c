/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unsetenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 18:10:54 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/18 22:46:42 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			mn_freesave(char **save, int to_free)
{
	int	i;

	i = 0;
	if (to_free == 0)
		return ;
	if (!(save[0]))
	{
		free(save);
		return ;
	}
	while (save[i])
	{
		free(save[i]);
		save[i] = NULL;
		i++;
	}
	free(save);
}

static void		mn_goaway(t_mini *infos, int b)
{
	char	**save;
	int		i;
	int		a;

	i = 0;
	if (infos->envon == 1)
		infos->unenv = 1;
	save = infos->env;
	while (infos->env[i])
		i++;
	if (!(infos->env = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
		return ;
	infos->envon = 1;
	i = 0;
	a = -1;
	while (save[i])
	{
		if (i != b)
			infos->env[++a] = ft_strdup(save[i]);
		i++;
	}
	infos->env[++a] = NULL;
	mn_freesave(save, infos->unenv);
	mn_getpath(infos);
	return ;
}

int				mn_unsetenv2(t_mini *infos)
{
	int	i;

	i = 0;
	while (infos->env[i])
	{
		if (ft_strncmp(infos->env[i], infos->flags[1],
					ft_strlen(infos->flags[1])) == 0)
			mn_goaway(infos, i);
		i++;
	}
	return (1);
}

int				mn_envu(t_mini *infos)
{
	int		i;

	i = 0;
	while (infos->flags[i] && infos->flags[i + 1])
	{
		free(infos->flags[i]);
		infos->flags[i] = NULL;
		infos->flags[i] = ft_strdup(infos->flags[i + 1]);
		i++;
	}
	if (infos->flags[i])
	{
		free(infos->flags[i]);
		infos->flags[i] = NULL;
	}
	return (mn_unsetenv2(infos));
}
