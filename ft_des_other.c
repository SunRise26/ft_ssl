/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 19:17:21 by vveselov          #+#    #+#             */
/*   Updated: 2018/03/02 14:15:16 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned char	*des_strj(char **str, int len)
{
	int				i;
	int				j;
	int				k;
	unsigned char	*s;
	unsigned char	*buf;

	j = len / 8;
	if (len % 8)
		j += 1;
	i = 8 * j++ + 1;
	s = (unsigned char *)malloc(i);
	s[i] = '\0';
	while (--j)
	{
		i = (len / 8) - j;
		if (len % 8)
			i += 1;
		buf = hex_out(str[i], HEXN);
		k = -1;
		while (++k < 8)
			s[k + (8 * i)] = buf[k];
		free(buf);
	}
	return (s);
}

unsigned char	*des_pad(unsigned char **s, int *i)
{
	int				j;
	int				c;
	unsigned char	*new;
	unsigned char	*pad;

	c = 8 - *i % 8;
	pad = (unsigned char *)malloc(c);
	j = -1;
	while (++j < c)
		pad[j] = c;
	new = ft_strj(*s, pad, *i, c);
	free(*s);
	free(pad);
	*i += c;
	return (new);
}

int				new_k(unsigned char *str, int *k)
{
	int		res;
	int		i;

	res = *k;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	*k = (i / 4) * 3;
	if (i % 4)
		*k += (i % 4) - 1;
	return (res);
}

int				ft_base64ad(unsigned char *str, char *key, int k1)
{
	int		i;
	int		j;

	i = -1;
	while (++i < k1 && (j = -1))
		if (str[i] == '=')
			str[i] = '\0';
		else
			while (key[++j])
				if (key[j] == str[i])
				{
					str[i] = j;
					break ;
				}
	return (i);
}

void			res_free(char **res)
{
	int		j;

	j = 0;
	while (res[j])
		free(res[j++]);
	free(res[j]);
	free(res);
}
