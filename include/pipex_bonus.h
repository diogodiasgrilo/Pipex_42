/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:22:54 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/01 18:35:10 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include "../libft/libft.h"

# define ERR_INFILE "infile"
# define ERR_OUTFILE "outfile"
# define ERR_INPUT "invalid number of arguments.\n"
# define ERR_PATHS "couldn't find paths.\n"
# define ERR_PIPE "pipe"
# define ERR_FORK "fork failed"
# define ERR_CMD1 "command not found: "
# define ERR_CMD2 "no such file or directory: "

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
#endif

typedef struct s_data
{
	char	**envp_paths;
	char	**args;
	char	*arg_path;
	int		pipe[2];
    int		old_pipe;
	int		i;
	int		pid;
	int		infile;
	int		outfile;
	int		here_doc;
}               pipex_info;

void	cmd_error(char *cmd);
void	err_msg_exit(char *error);
int		sort_arg(pipex_info *info);
int		custm_err_msg(char *error);
void	free_split(char **strings);
int		sort_arg(pipex_info *info);
void	shut_pipe(pipex_info *info);
int		check_char(pipex_info *info);
int		check_char(pipex_info *info);
int		get_line(int fd, char *delim);
int		try_paths(pipex_info *data, int j);
void	args_prep(pipex_info *info, char **argv);
void	handle_pipes(pipex_info *info, int argc, char **argv);
void	child_process(pipex_info *info, int argc, char **argv, char **envp);

#endif