/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc_ed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 21:10:39 by vveselov          #+#    #+#             */
/*   Updated: 2018/03/02 14:40:27 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	block_cbc_e(char **str, unsigned long long int *key,
				unsigned long long int iv)
{
	unsigned int			*lrb;
	unsigned long long int	block;
	int						i;
	int						j;
	unsigned int			sb;

	i = -1;
	while (str[++i] && !(j = 0))
	{
		lrb = llu_div(bl_ip(bl64(str[i], HEXN) ^ iv, IP));
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
		iv = block;
		hex64(str[i], block, HEXN);
		free(lrb);
	}
}

char	**des_cbc_e(unsigned char **s1, char **s2, int *i, int a)
{
	char					**str;
	unsigned int			*key;
	unsigned int			*key16;
	unsigned long long int	*key48;
	unsigned char			*buf;

	str = ch_hex(*s1, HEXN, i);
	key = pc_one(bl64(s2[0], HEXN), PC1);
	key16 = lshift(key);
	key48 = pc_two(key16, PC2);
	block_cbc_e(str, key48, bl64(s2[1], HEXN));
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

void	block_cbc_d(char **str, unsigned long long int *key,
					unsigned long long int iv)
{
	unsigned long long int	block;
	int						i;
	int						j;
	unsigned int			*lrb;
	unsigned int			sb;

	i = -1;
	while (str[++i] && (j = 15))
	{
		lrb = llu_div(fin_ip(bl64(str[i], HEXN), RFIP));
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
		iv = bl64(str[i], HEXN);
		hex64(str[i], block, HEXN);
		free(lrb);
	}
}

char	**des_cbc_d(unsigned char **s1, char **s2, int *i, int a)
{
	char					**str;
	unsigned int			*key;
	unsigned int			*key16;
	unsigned long long int	*key48;
	unsigned char			*buf;

	if (a)
	{
		buf = (unsigned char *)ft_base64d(s1, MIME, i);
		free(*s1);
		*s1 = buf;
	}
	str = ch_hex(*s1, HEXN, i);
	key = pc_one(bl64(s2[0], HEXN), PC1);
	key16 = lshift(key);
	key48 = pc_two(key16, PC2);
	block_cbc_d(str, key48, bl64(s2[1], HEXN));
	free(key);
	free(key16);
	free(key48);
	free(*s1);
	*s1 = des_strj(str, *i);
	pad_ch(i, *s1);
	return (str);
}
