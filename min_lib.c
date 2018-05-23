/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 18:07:47 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/23 18:03:50 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

size_t			ft_strlen(char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void			ft_putendl(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
	write(1, "\n", 1);
}

char			*word_in_br(char *s)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * (len + 3));
	res[0] = '\"';
	i = 0;
	while (s[i++])
		res[i] = s[i - 1];
	res[i++] = '\"';
	res[i] = '\0';
	return (res);
}

void			free_word(unsigned int **word, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		free(word[i]);
	free(word);
}

void			ft_toupper(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
}
