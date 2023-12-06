/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohassani <ohassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:48:34 by ohassani          #+#    #+#             */
/*   Updated: 2023/12/06 18:50:05 by ohassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

static char	*readmybuffer(int fd, char *accumulation, char *buffer)
{
	int		i;
	char	*tmp;

	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(accumulation);
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
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (accumulation);
}

// int main ()
// {
//   char d [] = "efrgdfgdgffdgdgdf wefsdfefsafsafds efresfsefsefesf";
//   int fd = open("file.txt", O_RDWR | O_CREAT);
//   char *s;

//   readmybuffer(fd, s, d);
// }
