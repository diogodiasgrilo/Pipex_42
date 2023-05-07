/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:03:37 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/01 20:28:09 by diogpere         ###   ########.fr       */
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
	while (strings[i])
		free(strings[i++]);
	free(strings);
}

int	get_paths(t_info *data, char **envp)
{
	int	j;

	j = -1;
	while (envp[++j])
	{
		if (ft_strncmp(envp[j], "PATH=", 5) == 0)
		{
			data->envp_paths = ft_split(&envp[j][5], ':');
			return (1);
		}
	}
	return (-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;

	if (argc != 5)
		return (custm_err_msg(ERR_INPUT));
	info = ft_calloc(1, sizeof(t_info));
	info->i = 1;
	if (!get_paths(info, envp))
		return (custm_err_msg(ERR_PATHS));
	if (pipe(info->pipe) < 0)
		err_msg_exit(ERR_PIPE);
	while ((++(info->i) <= argc - 2))
	{
		args_prep(info, argv);
		child_process(info, argv, envp);
		free_split(info->args);
		free(info->arg_path);
	}
	shut_pipe(info);
	while (info->i-- != argc - 3)
		waitpid(-1, NULL, 0);
	free_split(info->envp_paths);
	free(info);
	return (0);
}
