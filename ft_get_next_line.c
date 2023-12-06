/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:34:53 by ohassani          #+#    #+#             */
/*   Updated: 2023/12/06 19:52:26 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void freee(void *str)
{
	free(str);
	str = NULL;
}
char *get_next_line(int fd)
{
	char *line;
	char *buffer;
	static char *accumulation;

	line = NULL;
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (fd < 0 || read(fd, 0, 0) || BUFFER_SIZE <= 0)
	{
		freee(accumulation);
		freee(buffer);
		return (NULL);
	}
	if (!buffer)
		return (NULL);
}

static char *readmybuffer(int fd, char *accumulation, char *buffer)
{
	int i;
	char *tmp;

	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			freee(accumulation);
			return (NULL);
		}
		else if (i == 0)
			break;
		buffer[i] = '\0';
		if (!accumulation)
			accumulation = ft_strdup("");
		tmp = accumulation;
		accumulation = ft_strjoin(tmp, buffer);
		freee(tmp);
		if (ft_strchr(buffer, '\n'))
			break;
	}
	return (accumulation);
}

char *set_line(char *line_buffer)
{
	char *accumulation;

	int i = 0;
	while (line_buffer[i] != '\0' || line_buffer[i] != '\n')
		i++;
	if(line_buffer[i] == '\0')
		return(NULL);
	accumulation = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer - i));
	if (*accumulation == '\0')
		freee(accumulation);
	line_buffer[i + 1] = '\0';
	return (accumulation);
}
// int main ()
// {
// 	int fd = open("test.c",O_RDONLY);
// 	char *t = get_next_line(fd);
// 	printf("%s", t);
// }