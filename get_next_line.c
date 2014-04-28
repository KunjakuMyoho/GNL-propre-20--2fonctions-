/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aardjoun <aardjoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/15 15:11:04 by aardjoun          #+#    #+#             */
/*   Updated: 2014/04/24 11:06:08 by aardjoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					get_next_line_save(char *line, char *buf, char *save)
{
	int				i;
	int				j;

	j = 0;
	i = ft_strlen(line);
	while (buf[j])
	{
		if (buf[j] == '\n')
		{
			line[i] = '\0';
			j++;
			save = ft_strcpy(save, buf + j);
			return (1);
		}
		line[i++] = buf[j++];
	}
	save[0] = '\0';
	line[i] = '\0';
	return (0);
}

int					get_next_line(int const fd, char **line)
{
	static char		save[BUFF_SIZE];
	int				ret;
	char			*buf;

	if (fd == -1)
		return (-1);
	buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	*line = (char *)malloc(sizeof(char) * BUFF_SIZE);
	if (!buf || !(*line))
		return (-1);
	*line[0] = '\0';
	if (get_next_line_save(*line, save, save) == 1)
		return (1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (get_next_line_save(*line, buf, save) == 1)
			return (1);
	}
	free(*line);
	*line = NULL;
	return (0);
}
