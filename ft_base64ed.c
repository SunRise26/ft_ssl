/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64ed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:34:30 by vveselov          #+#    #+#             */
/*   Updated: 2018/03/02 15:14:58 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		shift_base64(int *j, char *res, unsigned char *str, char *key)
{
	unsigned char	ch;

	res[(j[1])++] = key[str[++(j[0])] >> 2];
	ch = str[j[0]] << 6;
	ch = ch >> 2;
	res[(j[1])++] = key[ch | str[++(j[0])] >> 4];
	if (j[0] >= j[2])
		return (1);
	ch = str[j[0]] << 4;
	ch = ch >> 2;
	res[(j[1])++] = key[ch | str[++(j[0])] >> 6];
	if (j[0] >= j[2])
		return (1);
	ch = str[j[0]] << 2;
	ch = ch >> 2;
	res[(j[1])++] = key[ch];
	return (0);
}

int		ft_base64e_res(unsigned char *str, char *res, char *key, int k)
{
	int				j[3];
	int				i;

	j[0] = -1;
	j[1] = 0;
	j[2] = k;
	i = 0;
	while (j[0] + 1 < k)
	{
		if (shift_base64(j, res, str, key))
			break ;
		if (++i == 16)
		{
			i = 0;
			res[(j[1])++] = '\n';
		}
	}
	return (j[1]);
}

char	*ft_base64e(unsigned char **str, char *key, int *k)
{
	char	*res;
	int		i;
	int		ct;

	i = *k;
	ct = (i / 3) * 4;
	if (i % 3)
		ct += 4;
	i = ct;
	while (i > 64 && ++ct)
		i -= 64;
	res = (char *)malloc(sizeof(char) * (ct + 1));
	i = ct;
	ct = ft_base64e_res(*str, res, key, *k);
	while (ct < i)
		res[ct++] = '=';
	res[ct++] = '\n';
	if (i != 0)
		*k = i + 1;
	return (res);
}

int		ft_base64d_res(unsigned char *str, char *res, int k)
{
	int				j;
	int				ct;
	unsigned char	ch;

	j = -1;
	ct = 0;
	while (++j < k)
	{
		ch = str[j] << 2;
		res[ct++] = ch | str[++j] >> 4;
		if (j >= k)
			break ;
		ch = str[j] << 4;
		res[ct++] = ch | str[++j] >> 2;
		if (j >= k)
			break ;
		ch = str[j] << 6;
		res[ct++] = (ch | str[++j]);
	}
	return (ct);
}

char	*ft_base64d(unsigned char **str, char *key, int *k)
{
	char	*res;
	int		i;
	int		ct;
	int		k1;

	ft_base64wh(str, *k);
	k1 = new_k(*str, k);
	i = ft_base64ad(*str, key, k1);
	ct = (i / 4) * 3;
	res = (char *)malloc(sizeof(char) * (ct + 1));
	i = ct;
	ct = ft_base64d_res(*str, res, k1);
	while (ct <= i)
		res[ct++] = '\0';
	return (res);
}
