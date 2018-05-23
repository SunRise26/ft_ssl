/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:16:48 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/23 18:07:48 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			sha256_len_pad(unsigned long long len, unsigned char **s, int i)
{
	(*s)[i] = len >> 56;
	(*s)[i + 1] = (len << 8) >> 56;
	(*s)[i + 2] = (len << 16) >> 56;
	(*s)[i + 3] = (len << 24) >> 56;
	(*s)[i + 4] = (len << 32) >> 56;
	(*s)[i + 5] = (len << 40) >> 56;
	(*s)[i + 6] = (len << 48) >> 56;
	(*s)[i + 7] = (len << 56) >> 56;
}

unsigned char	*sha256_pad(char *s, int *size)
{
	unsigned long long	len;
	unsigned char		*pad_s;
	unsigned char		*new;
	int					pad;
	int					i;

	len = ft_strlen(s) * 8;
	pad = len % 512;
	if (pad < 448)
		pad = 448 - pad;
	else
		pad = 960 - pad;
	pad = (pad + 64) / 8;
	pad_s = (unsigned char *)malloc(sizeof(unsigned char) * pad);
	i = 0;
	pad_s[i] = 128;
	while (++i < pad - 8)
		pad_s[i] = 0;
	sha256_len_pad(len, &pad_s, i);
	new = ft_strj((unsigned char *)s, pad_s, len / 8, pad);
	free(pad_s);
	*size = (len / 8 + pad) / 64;
	return (new);
}

unsigned int	**sha256_words_conv(unsigned char *s, int size)
{
	unsigned int	**word;
	int				i;
	int				j;

	word = (unsigned int **)malloc(sizeof(unsigned int *) * size);
	i = -1;
	while (++i < size && (j = -1))
	{
		word[i] = (unsigned int *)malloc(sizeof(unsigned int) * 16);
		while (++j < 16)
		{
			word[i][j] = 0;
			word[i][j] |= (unsigned int)(*s++) << 24;
			word[i][j] |= (unsigned int)(*s++) << 16;
			word[i][j] |= (unsigned int)(*s++) << 8;
			word[i][j] |= (unsigned int)(*s++);
		}
	}
	return (word);
}

char			*sha256_output_conv(unsigned int hash[8])
{
	char			*out;
	int				i;
	int				j;
	unsigned char	hex_n;

	i = -1;
	j = 0;
	out = (char *)malloc(sizeof(char) * 65);
	out[64] = '\0';
	while (++i < 64)
	{
		hex_n = (hash[j] << ((i % 8) * 4)) >> 24;
		out[i++] = HEXD[(hex_n / 16) % 16];
		out[i] = HEXD[hex_n % 16];
		if (!((i + 1) % 8))
			j++;
	}
	return (out);
}

char			*sha256_e(char *s)
{
	unsigned char	*str;
	int				size;
	unsigned int	**word;
	unsigned int	hash[8];

	str = sha256_pad(s, &size);
	word = sha256_words_conv(str, size);
	free(str);
	hash[0] = SHA256_A;
	hash[1] = SHA256_B;
	hash[2] = SHA256_C;
	hash[3] = SHA256_D;
	hash[4] = SHA256_E;
	hash[5] = SHA256_F;
	hash[6] = SHA256_G;
	hash[7] = SHA256_H;
	sha256_process(word, size, hash);
	free_word(word, size);
	return (sha256_output_conv(hash));
}
