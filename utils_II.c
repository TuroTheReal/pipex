/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_II.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:20:01 by artberna          #+#    #+#             */
/*   Updated: 2024/07/18 14:21:17 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_arg(char *av)
{
	char	*tmp;

	tmp = ft_strtrim(av, " ");
	if (ft_strlen(tmp) == 0)
		return (free(tmp), FALSE);
	free(tmp);
	return (TRUE);
}
