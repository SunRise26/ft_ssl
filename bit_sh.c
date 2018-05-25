/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_sh.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:51:11 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/25 17:11:34 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	bits_rot(unsigned int n, unsigned int bits)
{
	return (((n) << (bits)) | ((n) >> (32 - (bits))));
}

unsigned int	bits_rot_rev(unsigned int n, unsigned int bits)
{
	return (((n) >> (bits)) | ((n) << (32 - (bits))));
}

void			ft_toupper(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
}

void			ft_tolower(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
}
