/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:34:53 by ohassani          #+#    #+#             */
/*   Updated: 2023/12/16 11:42:22 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **buffer)

{
	free(*buffer);
	*buffer = NULL;
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*accumulation = NULL;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	line = mybuffer(fd, accumulation, buffer);
	if (line == NULL || line[0] == '\0')
	{
		if (accumulation != NULL)
			ft_free(&accumulation);
		return (NULL);
	}
	accumulation = linesub(line);
	return (line);
}

char	*mybuffer(int fd, char *accumulation, char *buffer)
{
	ssize_t	i;
	char	*tmp;

	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			ft_free(&buffer);
			return (NULL);
		}
		else if (i == 0)
			break ;
		buffer[i] = '\0';
		if (!accumulation)
			accumulation = ft_strdup("");
		tmp = accumulation;
		accumulation = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	ft_free(&buffer);
	return (accumulation);
}

char	*linesub(char *line_buffer)
{
	char	*accumulation;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\0')
		return (NULL);
	accumulation = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (!accumulation)
		return (NULL);
	line_buffer[i + 1] = '\0';
	return (accumulation);
}
