/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:35:20 by vveselov          #+#    #+#             */
/*   Updated: 2018/03/02 15:00:24 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	sbox(unsigned long long int c, char *s, int sh)
{
	unsigned char	col;
	unsigned int	n;

	c = c << sh;
	c = c >> 58;
	col = c;
	col = col >> 5;
	col = col << 1;
	col |= c & 1;
	n = c;
	n = n << 27;
	n = n >> 28;
	n = s[n + (16 * col)];
	return (n);
}

unsigned int	sboxes(unsigned long long int n)
{
	unsigned int			res;

	res = 0;
	res |= sbox(n, S1, 16);
	res = res << 4;
	res |= sbox(n, S2, 22);
	res = res << 4;
	res |= sbox(n, S3, 28);
	res = res << 4;
	res |= sbox(n, S4, 34);
	res = res << 4;
	res |= sbox(n, S5, 40);
	res = res << 4;
	res |= sbox(n, S6, 46);
	res = res << 4;
	res |= sbox(n, S7, 52);
	res = res << 4;
	res |= sbox(n, S8, 58);
	return (res);
}

void			block_e(char **str, unsigned long long int *key)
{
	unsigned int			*lrb;
	unsigned long long int	block;
	int						i;
	int						j;
	unsigned int			sb;

	i = -1;
	while (str[++i])
	{
		lrb = llu_div(bl_ip(bl64(str[i], HEXN), IP));
		j = 0;
		while (j < 16)
		{
			sb = lrb[1];
			block = pr_ebit(lrb[1], key[j], EBIT);
			lrb[1] = sboxes(block);
			lrb[1] = perm(lrb[1], PER);
			lrb[1] = lrb[1] ^ lrb[0];
			lrb[0] = sb;
			j += 1;
		}
		block = fin_ip(uint_join(lrb[1], lrb[0], 32), FIP);
		hex64(str[i], block, HEXN);
		free(lrb);
	}
}

char			**des_e(unsigned char **s1, char *s2, int *i, int a)
{
	char					**str;
	unsigned int			*key;
	unsigned int			*key16;
	unsigned long long int	*key48;
	unsigned char			*buf;

	str = ch_hex(*s1, HEXN, i);
	key = pc_one(bl64(s2, HEXN), PC1);
	key16 = lshift(key);
	key48 = pc_two(key16, PC2);
	block_e(str, key48);
	free(key);
	free(key16);
	free(key48);
	free(*s1);
	*s1 = des_strj(str, *i);
	if (a)
	{
		buf = (unsigned char *)ft_base64e(s1, MIME, i);
		free(*s1);
		*s1 = buf;
	}
	return (str);
}
