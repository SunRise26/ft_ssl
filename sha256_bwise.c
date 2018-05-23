/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_bwise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:58:02 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/23 18:07:25 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	sha256_ch(unsigned int x, unsigned int y, unsigned int z)
{
	return (((x) & (y)) ^ ((~x) & (z)));
}

unsigned int	sha256_maj(unsigned int x, unsigned int y, unsigned int z)
{
	return ((((x) & (y)) ^ ((x) & (z))) ^ ((y) & (z)));
}

unsigned int	sha256_sigma(unsigned int x, int t)
{
	if (t == 0)
	{
		return ((bits_rot_rev(x, 2) ^ bits_rot_rev(x, 13)) ^
				bits_rot_rev(x, 22));
	}
	return ((bits_rot_rev(x, 6) ^ bits_rot_rev(x, 11)) ^ bits_rot_rev(x, 25));
}

unsigned int	sha256_delta(unsigned int x, int t)
{
	if (t == 0)
		return ((bits_rot_rev(x, 7) ^ bits_rot_rev(x, 18)) ^ (x >> 3));
	return ((bits_rot_rev(x, 17) ^ bits_rot_rev(x, 19)) ^ (x >> 10));
}
