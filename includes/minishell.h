/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-moul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 12:50:44 by cde-moul          #+#    #+#             */
/*   Updated: 2019/06/24 13:29:35 by cde-moul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libftprintf.h"
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/types.h> 
# include <sys/stat.h>
# include <sys/wait.h>

# define FIRST_LETTERS "ecsu"

typedef struct		s_mini
{
	char	**env;
	char	**path;
	char	**flags;
	char	*cmd;
	char	*previous_path;
	int		pathon;
	int		flagson;
	int		skipenv;
}					t_mini;

int			mn_cd(t_mini *infos);
int			mn_env(t_mini *infos);
int			mn_echo(t_mini *infos);
int			mn_read(t_mini *infos);
int			mn_setenv(t_mini *infos);
int			mn_getpath(t_mini *infos);
int			mn_unsetenv(t_mini *infos);
int			mn_checkarg(t_mini *infos);
int			mn_checkenv(t_mini *infos);
int			mn_setenvarg(t_mini *infos);
int			mn_treat(t_mini *infos, char *line);
int			mn_getarg(t_mini *infos, char *line);
void		mn_error_cd1(char *path);
void		mn_freeflags(t_mini *infos);
void		mn_error_cd2(char *path, struct stat *in);
#endif
