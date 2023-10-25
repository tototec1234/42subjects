/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torinoue <torinoue@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:14:14 by torinoue          #+#    #+#             */
/*   Updated: 2023/06/14 17:02:58 by torinoue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	get_newline_pos(char *str);
static char	*read_and_store(char *str, int fd, int *bytes_read);
static char	*extrct_line_and_renew_storage(char **storage_ptr, int newline_pos);
static char	*duplicate_line_and_clear_storage(char **storage);

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage[OPEN_MAX + 1];
	int			newline_pos;
	int			bytes_read[1];

	if (fd < 0 || OPEN_MAX < fd)
		return (NULL);
	newline_pos = get_newline_pos(storage[fd]);
	*bytes_read = LOOP_CONDITION_INIT_VALUE;
	while (newline_pos == 0 && *bytes_read > 0)
	{
		storage[fd] = read_and_store(storage[fd], fd, bytes_read);
		if (storage[fd] == NULL)
			return (free_and_rest_memory(&storage[fd]));
		newline_pos = get_newline_pos(storage[fd]);
	}
	line = NULL;
	if (newline_pos)
		line = extrct_line_and_renew_storage(&storage[fd], newline_pos);
	else if (ft_strlen(storage[fd]))
		line = duplicate_line_and_clear_storage(&storage[fd]);
	else
		free_and_rest_memory(&storage[fd]);
	return (line);
}

static int	get_newline_pos(char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static char	*read_and_store(char *str, int fd, int *bytes_read)
{
	char	*buf;
	char	*buf_joined;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (free_and_rest_memory(&str));
	*bytes_read = read(fd, buf, BUFFER_SIZE);
	if (*bytes_read < 0)
		return (free_and_rest_memory(&buf));
	buf[*bytes_read] = '\0';
	buf_joined = ft_strjoin(str, buf);
	free_and_rest_memory(&str);
	free_and_rest_memory(&buf);
	return (buf_joined);
}

static char	*extrct_line_and_renew_storage(char **storage_ptr, int newline_pos)
{
	char	*line;
	char	*temp;
	int		i;

	line = (char *)malloc(sizeof(char) * (newline_pos + 1));
	if (line == NULL)
		return (free_and_rest_memory(storage_ptr));
	i = 0;
	while (i < newline_pos)
	{
		line[i] = (*storage_ptr)[i];
		i++;
	}
	line[newline_pos] = '\0';
	temp = *storage_ptr;
	*storage_ptr = ft_strdup(&temp[newline_pos]);
	free_and_rest_memory(&temp);
	if (*storage_ptr == NULL)
		return (NULL);
	return (line);
}

static char	*duplicate_line_and_clear_storage(char **storage)
{
	char	*line;

	line = ft_strdup(*storage);
	free_and_rest_memory(storage);
	return (line);
}

/*
 #include <fcntl.h>
 #include <stdio.h>
 int main()
 {
 	char *test = "";
 	int fd1 = open("test1", O_RDONLY);
	int fd2 = open("test2", O_RDONLY);
 	while (test)
 	{
 		test = get_next_line(fd1);
 		printf("fd1:%s", test);
 		free(test);
 		test = get_next_line(fd2);
 		printf("fd2:%s", test);
 		free(test);
 	}
 	close(fd1);
 	close(fd2);
 }

__attribute__((destructor))
static void destructor() {
	system("leaks -q a.out");
}
*/
/*
cc get_next_line_bonus.c get_next_line_utils_bonus.c get_next_line_bonus.h
 -Wall -Wextra -Werror -D BUFFER_SIZE=4 && ./a.out |cat -e
*/