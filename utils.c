/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:00:46 by artberna          #+#    #+#             */
/*   Updated: 2024/07/18 14:21:06 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_err_input(void)
{
	ft_putstr_fd("Wrong input!\n", 2);
	ft_putstr_fd("Try : \"./exec infile cmd1 cmd2 outfile\".\n", 2);
}

void	close_pipes(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

static void	choose_exit_p2(int option, char *message, char *str, char **tab)
{
	if (option == 3)
	{
		free_double(tab);
		perror(message);
		exit (EXIT_FAILURE);
	}
	if (option == 4)
	{
		free(str);
		free_double(tab);
		perror(message);
		exit (EXIT_FAILURE);
	}
}

void	choose_exit(int option, char *message, char *str, char **tab)
{
	if (option == 0)
		exit (EXIT_SUCCESS);
	if (option == 1)
	{
		perror(message);
		exit (EXIT_FAILURE);
	}
	if (option == 2)
	{
		free(str);
		perror(message);
		exit (EXIT_FAILURE);
	}
	else
		choose_exit_p2(option, message, str, tab);
}

void	**free_double(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}
