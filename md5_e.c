/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_e.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:21:08 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/23 13:53:59 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void			len_pad(unsigned long long len, unsigned char **s, int i)
{
	(*s)[i + 7] = len >> 56;
	(*s)[i + 6] = (len << 8) >> 56;
	(*s)[i + 5] = (len << 16) >> 56;
	(*s)[i + 4] = (len << 24) >> 56;
	(*s)[i + 3] = (len << 32) >> 56;
	(*s)[i + 2] = (len << 40) >> 56;
	(*s)[i + 1] = (len << 48) >> 56;
	(*s)[i] = (len << 56) >> 56;
}

unsigned char	*md5_pad(char *s, int *size)
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
	len_pad(len, &pad_s, i);
	new = ft_strj((unsigned char *)s, pad_s, len / 8, pad);
	free(pad_s);
	*size = (len / 8 + pad) / 64;
	return (new);
}

unsigned int	**words_conv(unsigned char *s, int size)
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
			word[i][j] |= (unsigned int)(*s++);
			word[i][j] |= (unsigned int)(*s++) << 8;
			word[i][j] |= (unsigned int)(*s++) << 16;
			word[i][j] |= (unsigned int)(*s++) << 24;
		}
	}
	return (word);
}

char			*md5_output_conv(unsigned int abcd[4])
{
	char			*out;
	int				i;
	int				j;
	unsigned char	hex_n;

	i = -1;
	j = 0;
	out = (char *)malloc(sizeof(char) * 33);
	out[32] = '\0';
	while (++i < 32)
	{
		hex_n = (abcd[j] << (24 - (i % 8) * 4)) >> 24;
		out[i++] = HEXD[(hex_n / 16) % 16];
		out[i] = HEXD[hex_n % 16];
		if (!((i + 1) % 8))
			j++;
	}
	return (out);
}

char			*md5_e(char *s)
{
	unsigned char	*str;
	int				size;
	unsigned int	**word;
	unsigned int	abcd[4];

	str = md5_pad(s, &size);
	word = words_conv(str, size);
	free(str);
	abcd[0] = MD5_A;
	abcd[1] = MD5_B;
	abcd[2] = MD5_C;
	abcd[3] = MD5_D;
	md5_process(word, size, abcd);
	free_word(word, size);
	return (md5_output_conv(abcd));
}
