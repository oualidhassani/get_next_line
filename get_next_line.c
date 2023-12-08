/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:34:53 by ohassani          #+#    #+#             */
/*   Updated: 2023/12/08 17:17:09 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*accumulation;

	line = NULL;
	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		free(accumulation);
		accumulation = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = readmybuffer(fd, accumulation, buffer);
	free(buffer);
	buffer = NULL;
	if (line == NULL || line[0] == '\0')
	{
		free(accumulation);
		return (NULL);
	}
	accumulation = set_line(line);
	return (line);
}

char	*readmybuffer(int fd, char *accumulation, char *buffer)
{
	ssize_t	i;
	char	*tmp;

	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (NULL);
		else if (i == 0)
			break ;
		buffer[i] = '\0';
		if (!accumulation)
			accumulation = ft_strdup("");
		tmp = accumulation;
		accumulation = ft_strjoin(accumulation, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (accumulation);
}

char	*set_line(char *line_buffer)
{
	char	*accumulation;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\0')
		return (NULL);
	accumulation = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (accumulation == 0)
		accumulation = NULL;
	line_buffer[i + 1] = 0;
	return (accumulation);
}

int main()
{
    int fd;
    char *line;
    fd = open("test.txt", O_RDONLY);
	// while((line = get_next_line(fd)))
	// {
	// 	printf("%s", line);
	// 	free(line);
	// }
	char *line1 = get_next_line(fd);
	char *line2 = get_next_line(fd);
	char *line3 = get_next_line(fd);
	printf("%s",line1);
	printf("%s",line2);
	printf("%s",line3);
	//system("leaks a.out");
	// line = get_next_line(fd);
	// printf("%s",line);
}