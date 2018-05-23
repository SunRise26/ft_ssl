/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_bwise_fun.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:29:56 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/23 12:36:13 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	md5_f(unsigned int x, unsigned int y, unsigned int z)
{
	return ((((x) & (y)) | ((~x) & (z))));
}

unsigned int	md5_g(unsigned int x, unsigned int y, unsigned int z)
{
	return (((x) & (z)) | ((y) & (~z)));
}

unsigned int	md5_h(unsigned int x, unsigned int y, unsigned int z)
{
	return ((x) ^ (y) ^ (z));
}

unsigned int	md5_i(unsigned int x, unsigned int y, unsigned int z)
{
	return ((y) ^ ((x) | (~z)));
}
