/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_sh.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:51:11 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/23 16:56:03 by vveselov         ###   ########.fr       */
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
