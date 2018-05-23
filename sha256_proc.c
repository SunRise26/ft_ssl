/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:42:24 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/23 18:04:21 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	sha256_set_buff(unsigned int buff[8], unsigned int h_cp[8],
						unsigned int hash[8])
{
	buff[0] = hash[0];
	buff[1] = hash[1];
	buff[2] = hash[2];
	buff[3] = hash[3];
	buff[4] = hash[4];
	buff[5] = hash[5];
	buff[6] = hash[6];
	buff[7] = hash[7];
	h_cp[0] = hash[0];
	h_cp[1] = hash[1];
	h_cp[2] = hash[2];
	h_cp[3] = hash[3];
	h_cp[4] = hash[4];
	h_cp[5] = hash[5];
	h_cp[6] = hash[6];
	h_cp[7] = hash[7];
}

void	sha256_set_64w(unsigned int sha256_w[64], unsigned int *word32)
{
	int		i;

	i = -1;
	while (++i < 16)
		sha256_w[i] = word32[i];
	while (i < 64)
	{
		sha256_w[i] = sha256_w[i - 16] + sha256_delta(sha256_w[i - 15], 0) +
		sha256_w[i - 7] + sha256_delta(sha256_w[i - 2], 1);
		i++;
	}
}

void	sha256_compression(unsigned int h_cp[8], unsigned int sha256_w[64],
							const unsigned int sha256_k[64])
{
	unsigned int	tmp1;
	unsigned int	tmp2;
	int				i;

	i = -1;
	while (++i < 64)
	{
		tmp1 = h_cp[7] + sha256_sigma(h_cp[4], 1) +
		sha256_ch(h_cp[4], h_cp[5], h_cp[6]) + sha256_w[i] + sha256_k[i];
		tmp2 = sha256_sigma(h_cp[0], 0) + sha256_maj(h_cp[0], h_cp[1], h_cp[2]);
		h_cp[7] = h_cp[6];
		h_cp[6] = h_cp[5];
		h_cp[5] = h_cp[4];
		h_cp[4] = h_cp[3] + tmp1;
		h_cp[3] = h_cp[2];
		h_cp[2] = h_cp[1];
		h_cp[1] = h_cp[0];
		h_cp[0] = tmp1 + tmp2;
	}
}

void	sha256_add_buff(unsigned int hash[8], unsigned int h_cp[8],
						unsigned int buff[8])
{
	hash[0] = buff[0] + h_cp[0];
	hash[1] = buff[1] + h_cp[1];
	hash[2] = buff[2] + h_cp[2];
	hash[3] = buff[3] + h_cp[3];
	hash[4] = buff[4] + h_cp[4];
	hash[5] = buff[5] + h_cp[5];
	hash[6] = buff[6] + h_cp[6];
	hash[7] = buff[7] + h_cp[7];
}

void	sha256_process(unsigned int **word, int size, unsigned int hash[8])
{
	const unsigned int	sha256_k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf,
0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98,
0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f,
0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8,
0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85,
0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e,
0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c,
0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee,
0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7,
0xc67178f2};
	unsigned int		sha256_w[64];
	unsigned int		buff[8];
	unsigned int		h_cp[8];
	int					i;

	i = -1;
	while (++i < size)
	{
		sha256_set_64w(sha256_w, word[i]);
		sha256_set_buff(buff, h_cp, hash);
		sha256_compression(h_cp, sha256_w, sha256_k);
		sha256_add_buff(hash, h_cp, buff);
	}
}
