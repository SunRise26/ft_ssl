/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:35:17 by vveselov          #+#    #+#             */
/*   Updated: 2018/03/02 14:43:58 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	block_d(char **str, unsigned long long int *key)
{
	unsigned long long int	block;
	int						i;
	int						j;
	unsigned int			*lrb;
	unsigned int			sb;

	i = -1;
	while (str[++i])
	{
		lrb = llu_div(fin_ip(bl64(str[i], HEXN), RFIP));
		j = 15;
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
		block = bl_ip(uint_join(lrb[1], lrb[0], 32), RIP);
		hex64(str[i], block, HEXN);
		free(lrb);
	}
}

void	pad_ch(int *i, unsigned char *s)
{
	int		j;
	int		c;
	int		k;

	j = *i - 1;
	if (j >= 0 && s[j] >= 1 && s[j] <= 8)
		c = s[j++];
	else
		return ;
	k = 0;
	while (--j >= 0 && s[j] == c)
		k++;
	if (k == c)
		*i -= k;
}

char	**des_d(unsigned char **s1, char *s2, int *i, int a)
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
	key = pc_one(bl64(s2, HEXN), PC1);
	key16 = lshift(key);
	key48 = pc_two(key16, PC2);
	block_d(str, key48);
	free(key);
	free(key16);
	free(key48);
	free(*s1);
	*s1 = des_strj(str, *i);
	pad_ch(i, *s1);
	return (str);
}
