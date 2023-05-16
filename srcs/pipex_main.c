/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:03:37 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/16 15:21:41 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	shut_pipe(t_info *info)
{
	close(info->pipe[0]);
	close(info->pipe[1]);
}

void	free_split(char **strings)
{
	int	i;

	i = 0;
	while (strings && strings[i])
		free(strings[i++]);
	free(strings);
}

void	get_paths(t_info *data, char **envp)
{
	int	j;

	j = -1;
	while (envp && envp[++j])
	{
		if (ft_strncmp(envp[j], "PATH=", 5) == 0)
		{
			data->envp_paths = ft_split(&envp[j][5], ':');
			return ;
		}
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	if (argc != 5)
		return (custm_err_msg(ERR_INPUT));
	info = ft_calloc(1, sizeof(t_info));
	check_file_error(info, argc, argv);
	info->i = 1;
	get_paths(info, envp);
	if (pipe(info->pipe) < 0)
		err_msg_exit(ERR_PIPE);
	while ((++(info->i) <= argc - 2))
	{
		if (!args_prep(info, argv))
			cmd_error(info->args[0]);
		else
			child_process(info, argv, envp);
		free_split(info->args);
		free(info->arg_path);
	}
	shut_pipe(info);
	while (info->i > 3)
	{
		waitpid(-1, 0, 0);
		info->i--;
	}
	free_split(info->envp_paths);
	free(info);
	return (0);
}
