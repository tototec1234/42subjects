/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: torinoue <torinoue@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:48:43 by torinoue          #+#    #+#             */
/*   Updated: 2023/06/14 17:04:14 by torinoue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		++len;
	return (len);
}

char	*ft_strdup(const char *src)
{
	char	*copied_string;
	size_t	i;

	if (src == NULL)
		return (NULL);
	copied_string = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (copied_string == NULL)
		return (free_and_rest_memory((char **)src));
		i = 0;
	while (src[i])
	{
		copied_string[i] = src[i];
		i++;
	}
	copied_string[i] = '\0';
	return (copied_string);
}

char	*free_and_rest_memory(char **memory)
{
	if (*memory != NULL)
		free(*memory);
	*memory = NULL;
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*joined;
	size_t	i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	size = 1;
	if (s1 != NULL)
		size += ft_strlen(s1);
	if (s2 != NULL)
		size += ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * size);
	if (joined == NULL)
		return (NULL);
	i = 0;
	if (s1 != NULL)
		while (*s1)
			joined[i++] = *s1++;
	if (s2 != NULL)
		while (*s2)
			joined[i++] = *s2++;
	joined[i] = '\0';
	return (joined);
}

/* The above code has been modified to return the non-NULL string
 if either *s1 or *s2 is NULL.
 This change is made to accommodate GNL (Get Next Line) functionality.
 The code below is the version that does not support GNL
  but intends to have the same behavior as the strjoin function
 in the standard library. */

/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*joined;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = (char *)ft_calloc(size, sizeof(char));
	if (joined == NULL)
		return (NULL);
	ft_strlcpy(joined, s1, size);
	ft_strlcat(joined, s2, size);
	return (joined);
}
*/
//if (copied_string == NULL)
//	return (NULL);
//		v
//		v
//		v
//		v
//if (copied_string == NULL)
//	return(free_and_rest_memory((char **)src));
