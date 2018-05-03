/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_cbc_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 21:10:39 by vveselov          #+#    #+#             */
/*   Updated: 2018/03/02 09:12:00 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned long long int	bl3_cbc_e(char *str, unsigned long long *key,
	unsigned long long int iv)
{
	unsigned int			*lrb;
	unsigned long long int	block;
	int						j;
	unsigned int			sb;

	j = 0;
	lrb = llu_div(bl_ip(bl64(str, HEXN) ^ iv, IP));
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
	free(lrb);
	return (block);
}

unsigned long long int	bl3_cbc_d(char *str, unsigned long long *key,
	unsigned long long int iv)
{
	unsigned int			*lrb;
	unsigned long long int	block;
	int						j;
	unsigned int			sb;

	j = 15;
	lrb = llu_div(fin_ip(bl64(str, HEXN), RFIP));
	while (j >= 0)
	{
		sb = lrb[1];
		block = pr_ebit(sb, key[j], EBIT);
		lrb[1] = sboxes(block);
		lrb[1] = perm(lrb[1], PER);
		lrb[1] = lrb[1] ^ lrb[0];
		lrb[0] = sb;
		j -= 1;
	}
	block = bl_ip(uint_join(lrb[1], lrb[0], 32), RIP) ^ iv;
	free(lrb);
	return (block);
}

void					block3_cbc_e(char **str, unsigned long long int **key,
				unsigned long long int iv)
{
	int					i;
	unsigned long long	sw;

	i = -1;
	while (str[++i])
	{
		iv = bl3_cbc_e(str[i], key[0], iv);
		hex64(str[i], iv, HEXN);
		sw = bl64(str[i], HEXN);
		iv = bl3_cbc_d(str[i], key[1], iv);
		hex64(str[i], iv, HEXN);
		iv = sw;
		iv = bl3_cbc_e(str[i], key[2], iv);
		hex64(str[i], iv, HEXN);
	}
}

void					block3_cbc_d(char **str, unsigned long long int **key,
				unsigned long long int iv)
{
	int					i;
	unsigned long long	sw;
	unsigned long long	sw1;

	i = -1;
	while (str[++i])
	{
		sw1 = bl64(str[i], HEXN);
		sw = bl3_cbc_d(str[i], key[2], 0);
		hex64(str[i], sw, HEXN);
		sw = bl3_cbc_e(str[i], key[1], 0);
		hex64(str[i], sw, HEXN);
		sw = bl3_cbc_d(str[i], key[0], iv);
		hex64(str[i], sw, HEXN);
		iv = sw1;
	}
}

void					des3_key48(unsigned long long int **key48, char **s2)
{
	unsigned int		*key;
	unsigned int		*key16;
	int					k;

	k = -1;
	while (++k < 3)
	{
		key = pc_one(bl64(&s2[0][k * 16], HEXN), PC1);
		key16 = lshift(key);
		free(key);
		key48[k] = pc_two(key16, PC2);
		free(key16);
	}
}
