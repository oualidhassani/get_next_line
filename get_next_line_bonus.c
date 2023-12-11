/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:50:42 by ohassani          #+#    #+#             */
/*   Updated: 2023/12/08 16:11:41 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *get_next_line(int fd)
{
	char *line;
	char *buffer;
	static char *accumulation[1024];

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647 
	|| read(fd, buffer, 0) < 0)
	{
		free(accumulation);
		accumulation = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	line = readmybuffer(fd, accumulation, buffer);
	if (line == NULL || line[0] == '\0')
	{
		if (accumulation != NULL)
		{
			free(accumulation);
			accumulation = NULL;
		}
		return (NULL);
	}
	accumulation = set_line(line);
	return (line);
}

char *readmybuffer(int fd, char *accumulation, char *buffer)
{
	ssize_t i;
	char *tmp;

	i = 1;
	if (!buffer)
		return (NULL);
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (NULL);
		else if (i == 0)
			break;
		buffer[i] = '\0';
		if (!accumulation)
			accumulation = ft_strdup("");
		tmp = accumulation;
		accumulation = ft_strjoin(accumulation, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break;
	}
	free(buffer);
	buffer = NULL;
	return (accumulation);
}

char *set_line(char *line_buffer)
{
	char *accumulation;
	ssize_t i;

	i = 0;
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\0')
		return (NULL);
	accumulation = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (!accumulation)
		return (NULL);
	line_buffer[i + 1] = 0;
	return (accumulation);
}

#include <stdio.h>
#include <fcntl.h>
int main ()
{
	int fd = open ("file.txt", O_RDONLY);

	int fd1 = open("test.txt", O_RDONLY);

	char *line;
	while((line = get_next_line(fd)))
	{
		printf("%s", line);
	}
}