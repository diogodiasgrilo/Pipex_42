/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_b_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogpere <diogpere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:03:37 by diogpere          #+#    #+#             */
/*   Updated: 2023/05/01 18:40:49 by diogpere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	shut_pipe(pipex_info *info)
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

int	get_paths(pipex_info *data, char **envp)
{
	int		j;

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
    pipex_info  *info;

    if (argc < 5)
        return (custm_err_msg(ERR_INPUT));
    info = ft_calloc(1, sizeof(pipex_info));
    info->i = 1;
    if (!get_paths(info, envp))
		return (custm_err_msg(ERR_PATHS));
	if (!(ft_strncmp("here_doc", argv[1], 8)))
	{
		info->here_doc = open("tmp.txt", O_CREAT| O_TRUNC | O_RDWR , 0644);
		while (1)
			if (!(get_line(info->here_doc, argv[2])))
				break;
		close(info->here_doc);
	}
    while ((++(info->i) <= argc - 2))
    {
		if (pipe(info->pipe) < 0)
			err_msg_exit(ERR_PIPE);
        args_prep(info, argv);
        child_process(info, argc, argv, envp);
		shut_pipe(info);
        free_split(info->args);
        free(info->arg_path);
           
    }
	// info->i = -1;
    waitpid(-1, 0, 0);
	unlink("tmp.txt");
    free_split(info->envp_paths);
    free(info);
    return (0);
}