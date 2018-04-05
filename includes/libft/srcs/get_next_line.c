/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-pass <gde-pass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:27:11 by gde-pass          #+#    #+#             */
/*   Updated: 2018/01/30 18:54:22 by gde-pass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static char				*ft_get_line_one(struct s_reste *content, char **line)
{
	char	*tmp;
	char	*buffy;
	int		i;

	tmp = NULL;
	i = 0;
	buffy = content->reste;
	while (buffy[i])
	{
		if (buffy[i] == '\n')
		{
			*line = ft_strsub(buffy, 0, i);
			tmp = buffy;
			buffy = ft_strdup(buffy + (i + 1));
			free(tmp);
			return (buffy);
		}
		i++;
	}
	*line = ft_strdup(buffy);
	ft_strclr(buffy);
	ft_strclr(content->reste);
	return (buffy);
}

static struct s_reste	*ft_load_first_call(const int fd)
{
	struct s_reste *tmp;

	if (!(tmp = malloc(sizeof(struct s_reste))))
		return (NULL);
	tmp->fd = fd;
	tmp->reste = ft_strnew(0);
	tmp->next = NULL;
	return (tmp);
}

static int				ft_read_fd(const int fd, struct s_reste *content)
{
	int		ret;
	char	buffy[BUFF_SIZE + 1];
	char	*tmp;

	ret = -100;
	tmp = NULL;
	while (!ft_strchr(content->reste, '\n'))
	{
		if ((ret = read(fd, buffy, BUFF_SIZE)) == 0)
			return (ENDREAD);
		buffy[ret] = '\0';
		tmp = content->reste;
		if (!(content->reste = ft_strjoin(content->reste, buffy)))
			return (ERROR);
		free(tmp);
		ft_bzero(buffy, (BUFF_SIZE + 1));
	}
	return (READLINE);
}

static void				ft_add_link(struct s_reste *reste, struct s_reste *tmp)
{
	while (reste->next != NULL)
		reste = reste->next;
	reste->next = tmp;
	tmp->next = NULL;
}

int						get_next_line(const int fd, char **line)
{
	static struct s_reste	*reste = NULL;
	struct s_reste			*tmp;
	ssize_t					ret;

	if (fd < 0 || BUFF_SIZE < 1 || line == NULL || read(fd, NULL, 0) == -1)
		return (ERROR);
	if (reste == NULL)
		reste = ft_load_first_call(fd);
	tmp = reste;
	while (tmp)
	{
		if (tmp->fd == fd)
			break ;
		if (tmp->next == NULL)
			ft_add_link(tmp, ft_load_first_call(fd));
		tmp = tmp->next;
	}
	if ((ret = ft_read_fd(fd, tmp)) < 0)
		return (ERROR);
	tmp->reste = ft_get_line_one(tmp, line);
	if (!ft_strlen(tmp->reste) && !ft_strlen(*line) && !ret)
		return (ENDREAD);
	return (READLINE);
}
