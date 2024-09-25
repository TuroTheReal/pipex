/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:49:54 by artberna          #+#    #+#             */
/*   Updated: 2024/07/18 14:20:48 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PIPEX_H
# define PIPEX_H

# include "my_library/my_library.h"

typedef enum e_error
{
	TRUE = 0,
	FALSE = 1,
}	t_error;

void	choose_exit(int option, char *message, char *str, char **tab);
void	**free_double(char **s);
int		check_arg(char *av);
void	close_pipes(int *fd);
void	print_err_input(void);

#endif