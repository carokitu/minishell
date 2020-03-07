/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:19:57 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/11 15:25:07 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		mn_geepwd2(t_mini *infos, int i, int a, int b)
{
	char	*prompt;

	prompt = ft_strsub(infos->env[i], a + 1, (b - a) + 3);
	ft_putstr(prompt);
	ft_putstr(" ~> ");
	free(prompt);
	return ;
}

void			mn_getpwd(t_mini *infos)
{
	int		i;
	int		a;
	int		b;
	char	*prompt;

	a = 0;
	i = mn_getline(infos->env, "PWD=", 4);
	if (i == -1)
		return ;
	b = ft_strlen(infos->env[i] + 4);
	if (b == 0)
		return ;
	a = b - 1;
	while (a > 4)
	{
		if (infos->env[i][a] == '/')
			return (mn_geepwd2(infos, i, a, b));
		a--;
	}
	prompt = ft_strsub(infos->env[i], a, b - a + 1);
	ft_putstr(prompt);
	ft_putstr("~>");
	free(prompt);
	return ;
}

static void		mn_promppt(char *dir, int a, int i)
{
	char	*tmp;

	tmp = dir;
	dir = ft_strsub(dir, (a + 1), i - 1);
	free(tmp);
	ft_putstr(dir);
	ft_putstr(" ~> ");
	free(dir);
	return ;
}

void			mn_prompt(t_mini *infos)
{
	char	*dir;
	int		i;
	int		a;

	dir = NULL;
	dir = getcwd(dir, 100);
	i = 0;
	if (dir)
		i = ft_strlen(dir);
	else
		return (mn_getpwd(infos));
	a = i;
	while (dir && --a >= 0 && dir[a])
	{
		if (dir[a] == '/' && a != (i - 1))
			return (mn_promppt(dir, a, i));
	}
	if (dir)
		ft_putstr(dir);
	ft_putstr(" ~> ");
	free(dir);
}
