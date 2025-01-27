/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:20 by bnafiai           #+#    #+#             */
/*   Updated: 2024/11/29 20:17:25 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*my_strchar(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	if (c == '\0')
		return (str + i);
	return (NULL);
}

size_t	my_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*my_strdup(char *s)
{
	size_t	i;
	char	*dup;
	size_t	len;

	i = 0;
	len = my_strlen(s) + 1;
	dup = malloc(len * sizeof(char));
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*my_strjoin(char *s1, char *s2)
{
	size_t	total_len;
	char	*str;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (my_strdup(s2));
	if (!s2)
		return (my_strdup(s1));
	total_len = my_strlen(s1) + my_strlen(s2) + 1;
	str = malloc(total_len);
	if (!str)
		return (NULL);
	i = 0;
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}
