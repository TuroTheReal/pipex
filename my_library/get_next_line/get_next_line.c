/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:30:20 by artberna          #+#    #+#             */
/*   Updated: 2024/07/08 12:55:22 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_library.h"

static char	*update_stash(char *stash)
{
	char	*new_sta;
	size_t	i;
	size_t	j;

	if (!stash)
		return (NULL);
	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
		return (free(stash), (NULL));
	new_sta = ft_calloc((ft_strlen(stash) - i + 1), sizeof(char));
	if (!new_sta)
		return (NULL);
	i++;
	while (stash[i])
		new_sta[j++] = stash[i++];
	new_sta[j] = '\0';
	free(stash);
	return (new_sta);
}

static char	*extract_line(char *str)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc (i + 2, sizeof(char));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*extend_stash(char *stash, char *buff)
{
	char		*temp;

	temp = ft_strjoin(stash, buff);
	if (!temp)
		return (NULL);
	free (stash);
	return (temp);
}

static char	*read_files(int fd, char *stash)
{
	int		byte_read;
	char	*buff;

	if (!stash)
		stash = ft_calloc (1, 1);
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buff, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(buff), (NULL));
		buff[byte_read] = '\0';
		stash = extend_stash(stash, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stash)
		{
			free(stash);
			stash = NULL;
		}
		return (NULL);
	}
	stash = read_files(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}

//read le fichier tant que pas de /n
//stocker dans le buff
//extraire vers reserve
//scanner reserve
//si \n, return la ligne et clean la reserve jusqu'qu \n
// garder le reste via variable static
