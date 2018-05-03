/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:28:17 by vveselov          #+#    #+#             */
/*   Updated: 2018/02/21 20:00:11 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char					**plain16(char **s)
{
	char	**res;
	int		i;
	int		k;
	int		j;
	int		y;

	i = 0;
	while ((*s)[i])
		i++;
	j = i / 16;
	res = (char **)malloc(sizeof(char *) * (j + 1));
	i = 0;
	k = -1;
	while (++k < j)
	{
		y = 0;
		res[k] = (char *)malloc(17);
		res[k][y++] = (*s)[i];
		while (++i % 16 || i == 0)
			res[k][y++] = (*s)[i];
		res[k][y] = '\0';
	}
	res[k] = NULL;
	free(*s);
	return (res);
}

char					**ch_hex(unsigned char *str, char *n, int *k)
{
	char	*hex;
	int		len;
	int		i;
	int		j;

	i = *k;
	if (i % 8)
		i += 8 - i % 8;
	len = i * 2;
	hex = (char *)malloc(len + 1);
	i = -1;
	j = 0;
	while (++i < *k)
	{
		hex[j++] = n[(str[i] / 16)];
		hex[j++] = n[(str[i] % 16)];
	}
	while (j < len)
		hex[j++] = '0';
	hex[j] = '\0';
	return (plain16(&hex));
}

unsigned long long int	bl64(char *s, char *hex)
{
	unsigned long long int	res;
	unsigned long long int	c;
	int						i;
	int						j;

	i = -1;
	res = 0;
	while (++i < 16)
	{
		j = -1;
		while (hex[++j])
			if (hex[j] == s[i])
				c = j;
		res = res << 4;
		res |= c;
	}
	return (res);
}

void					hex64(char *s, unsigned long long int n, char *hex)
{
	int						i;
	unsigned long long int	oct;

	i = 16;
	while (--i != -1)
	{
		oct = n;
		oct = oct << 60;
		oct = oct >> 60;
		s[i] = hex[oct];
		n = n >> 4;
	}
}

unsigned long long int	pr_ebit(unsigned int right,
						unsigned long long int key, char *ebit)
{
	unsigned long long int	new;
	int						i;

	new = 0;
	i = -1;
	while (ebit[++i])
	{
		new = new << 1;
		if ((right >> (32 - ebit[i])) & 1)
			new |= 1;
	}
	new ^= key;
	return (new);
}
