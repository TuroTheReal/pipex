/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:00:41 by artberna          #+#    #+#             */
/*   Updated: 2024/07/18 15:01:06 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	*get_final_path(char *av, char **env)
{
	char	**paths;
	int		i;
	char	*tmp;
	char	*final_path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		final_path = ft_strjoin(tmp, av);
		free(tmp);
		if (access(final_path, F_OK) == 0)
			return (free_double(paths), final_path);
		free(final_path);
		i++;
	}
	free_double(paths);
	return (NULL);
}

static void	exec_cmd(char *av, char **env)
{
	char	**final_path;
	char	*new_path;

	final_path = ft_split(av, ' ');
	if (!final_path)
		choose_exit(1, "SPLIT FAILED", NULL, NULL);
	if (access(final_path[0], F_OK) == 0)
	{
		if (execve(final_path[0], final_path, env) == -1)
			choose_exit(3, "EXECVE FAILED", NULL, final_path);
	}
	else
	{
		new_path = get_final_path(final_path[0], env);
		if (!new_path)
			choose_exit(3, "INVALID PATH", NULL, final_path);
		if (execve(new_path, final_path, env) == -1)
			choose_exit(4, "EXECVE FAILED", new_path, final_path);
	}
}

static void	child_process(int *pipefd, char **av, char **env)
{
	int	infile;

	if (check_arg(av[2]) == FALSE)
	{
		ft_putstr_fd("Empty commands.\n", 2);
		close_pipes(pipefd);
		exit(-1);
	}
	infile = open(av[1], O_RDONLY, 0777);
	if (infile == -1)
		choose_exit(1, "OPEN FAILED", NULL, NULL);
	if (dup2(infile, STDIN_FILENO) == -1)
		choose_exit(1, "DUP2 FAILED", NULL, NULL);
	close(infile);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		choose_exit(1, "DUP2 FAILED", NULL, NULL);
	close_pipes(pipefd);
	exec_cmd(av[2], env);
}

static void	second_child_process(int *pipefd, char **av, char **env)
{
	int	outfile;

	if (check_arg(av[3]) == FALSE)
	{
		ft_putstr_fd("Empty commands.\n", 2);
		close_pipes(pipefd);
		exit(-1);
	}
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		choose_exit(1, "OPEN FAILED", NULL, NULL);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		choose_exit(1, "DUP2 FAILED", NULL, NULL);
	close(outfile);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		choose_exit(1, "DUP2 FAILED", NULL, NULL);
	close_pipes(pipefd);
	exec_cmd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	pid_t	pid2;
	int		pipefd[2];

	if (ac != 5)
		return (print_err_input(), -1);
	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		child_process(pipefd, av, env);
	pid2 = fork();
	if (pid2 == -1)
		choose_exit(1, "FORK", NULL, NULL);
	if (pid2 == 0)
		second_child_process(pipefd, av, env);
	close_pipes(pipefd);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
