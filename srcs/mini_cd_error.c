/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 10:33:02 by cde-moul          #+#    #+#             */
/*   Updated: 2019/07/11 17:03:06 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				mn_cderror(t_mini *infos)
{
	if (!(infos->flags[1]))
		return (0);
	if (infos->flags[1] && infos->flags[2])
	{
		ft_putstr_fd("cd: Too many arguments.\n", STDOUT_FILENO);
		return (1);
	}
	return (0);
}
