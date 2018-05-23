/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_proc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:25:19 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/23 14:40:27 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	md5_rounds(unsigned int **word, int x, unsigned int *abcd,
		const unsigned int md5_t[64])
{
	int				i;
	int				j;
	const int		sw[4] = {0, 3, 2, 1};
	unsigned int	(*fun[4])(unsigned int, unsigned int, unsigned int);

	fun[0] = &md5_f;
	fun[1] = &md5_g;
	fun[2] = &md5_h;
	fun[3] = &md5_i;
	i = -1;
	j = 0;
	while (++i < 64)
	{
		abcd[sw[i % 4]] = abcd[(sw[i % 4] + 1) % 4] +
			bits_rot((abcd[sw[i % 4]] +
			fun[j](abcd[(sw[i % 4] + 1) % 4], abcd[(sw[i % 4] + 2) % 4],
			abcd[(sw[i % 4] + 3) % 4]) + word[x][(int)(MD5_K[i])] +
			md5_t[i]), MD5_S[i]);
		if (!((i + 1) % 16))
			j++;
	}
}

void	md5_add_buff(unsigned int abcd[4], unsigned int buff[4])
{
	abcd[0] = buff[0] + abcd[0];
	abcd[1] = buff[1] + abcd[1];
	abcd[2] = buff[2] + abcd[2];
	abcd[3] = buff[3] + abcd[3];
}

void	md5_process(unsigned int **word, int size, unsigned int abcd[4])
{
	const unsigned int	md5_t[64] = {0xd76aa478, 0xe8c7b756, 0x242070db,
0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8,
0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e,
0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d,
0x2441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87,
0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942,
0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60,
0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x4881d05, 0xd9d4d039,
0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7,
0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f,
0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb,
0xeb86d391};
	unsigned int		buff[4];
	int					i;

	i = -1;
	while (++i < size)
	{
		buff[0] = abcd[0];
		buff[1] = abcd[1];
		buff[2] = abcd[2];
		buff[3] = abcd[3];
		md5_rounds(word, i, abcd, md5_t);
		md5_add_buff(abcd, buff);
	}
}
