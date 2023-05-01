/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:35:52 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/01 11:05:50 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PIPEX_H
# define PIPEX_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include "../libft/libft.
h"

# define ERR_INFILE "infile"
# define ERR_OUTFILE "outfile"
# define ERR_INPUT "invalid number of arguments.\n"
# define ERR_PATHS "couldn't find paths.\n"
# define ERR_PIPE "pipe"
# define ERR_FORK "fork failed"
# define ERR_CMD1 "command not found: "
# define ERR_CMD2 "no such file or directory: "

typedef struct s_data
{
	char	**envp_paths;
	char	**args;
	char	*arg_path;
	int		pipe[2];
	int		i;
	int		pid;
	int		infile;
	int		outfile;
}               pipex_info;

void	free_split(char **);
void	shut_pipe(pipex_info *);
void	cmd_error_exit(char *cmd);
void	err_msg_exit(char *error);
int		sort_arg(pipex_info *info);
int		custm_err_msg(char *error);
int		check_char(pipex_info *info);
int		try_paths(pipex_info *data, int j);
void	handle_pipes(pipex_info *, char **);
int		args_prep(pipex_info *info, char **argv);
void	child_process(pipex_info *info, char **argv, char **envp);

#endif