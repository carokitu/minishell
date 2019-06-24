/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:51:08 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/24 16:49:04 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	mn_setenvv2(t_mini *infos, int a, char **save)
{
	int		i;
	char	*tmp;
	int		b;

	b = 0;
	i = 0;
	tmp = NULL;
	while (save[i])
	{
		printf("save : %s\n", save[i]);
		if (i == a)
		{
			infos->env[i] = NULL;
			tmp = ft_strjoin(infos->flags[1], "=");
			infos->env[i] = ft_strjoin(tmp, infos->flags[2]);
			free(tmp);
		}
		else
		{
			printf("savei[%d] : %s\n", i, save[i]);
			infos->env[i] = ft_strdup(save[i]);
			printf("PP: %s\n", infos->env[0]);
		}
		i++;
	}
	if (i >= a)
	{
		tmp = ft_strjoin(infos->flags[1] , "=");
		infos->env[i++] = ft_strjoin(tmp, infos->flags[2]);
		free(tmp);
	}
	infos->env[i] = NULL;
	i = -1;
	while (infos->env[++i])
	{
		printf("addresse de %d : %p\n", i, &infos->env[i]);
		printf("infos->env[%d] : %s\n", i, infos->env[i]);
	}
	return (0);
}

static char	**mn_tabdup(char **env)
{
	int 	i;
	char	**save;

	i = 0;
	while (env[i])
		i++;
	if (!(save = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (env[++i])
		save[i] = ft_strdup(env[i]);
	return (save);
}

static int	mn_setenvv(t_mini *infos, int a)
{
	int		i;
	char	**save;

	save = mn_tabdup(infos->env);
	i = 0;
	if (!(infos->flags[1]))
	{
		ft_putstr_fd("env: name should not be NULL\n", STDOUT_FILENO);
		return (1);
	}
	while (infos->flags[1][i])
	{
		if (infos->flags[1][i] == '=')
		{
			ft_putstr_fd("env: name must not contain '=' character\n",
					STDOUT_FILENO);
			return (1);
		}
		i++;
	}
	i = 0;
	while (infos->env[i])
		i++;	
	if (a == i)
		i++;
	if (!(infos->env = (char **)ft_memalloc(sizeof(char) * (i + 1))))
	{
		ft_putstr_fd("env: Insufficient memory to add a ", STDOUT_FILENO);
		ft_putstr_fd("new variable to the environment\n", STDOUT_FILENO);
		return (1);
	}
	return (mn_setenvv2(infos, a, save));
}

static int	mn_checkusage(t_mini *infos)
{
	if (!(infos->flags[1]) || !(infos->flags[2]) || !(infos->flags[3])
			|| infos->flags[4])
	{
		ft_putstr_fd("setenv: usage : [NAME] [value] [overwrite : 1 | 0]\n",
				STDOUT_FILENO);
		return (1);
	}	
	if (ft_strcmp(infos->flags[3], "0") != 0
			&& ft_strcmp(infos->flags[3], "1") != 0)
	{
		ft_putstr_fd("setenv: usage : [NAME] [value] [overwrite : 1 | 0]\n",
				STDOUT_FILENO);
		return (1);
	}
	return (0);
}

int			mn_setenvarg(t_mini *infos)
{
	int		i;
	char	*name;
	char	*value;
	char	*owrt;

	name = NULL;
	value = NULL;
	owrt = NULL;
	i = -1;
	if (mn_checkusage(infos) == 1)
		return (1);
	name = infos->flags[1];
	value = infos->flags[2];
	owrt = infos->flags[3];
	while (infos->env[++i])
	{
		if (ft_strncmp(infos->env[i], name, ft_strlen(name)) == 0)
		{
			if (owrt[0] == '0')
				return (0);
			return (mn_setenvv(infos, i));
		}
	}
	return (mn_setenvv(infos, i));
}
