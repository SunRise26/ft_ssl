/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:42:50 by vveselov          #+#    #+#             */
/*   Updated: 2018/02/21 20:01:02 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int			perm(unsigned int n, char *per)
{
	unsigned int	new;
	int				i;

	i = -1;
	new = 0;
	while (per[++i])
	{
		new = new << 1;
		if ((n >> (32 - per[i])) & 1)
			new |= 1;
	}
	return (new);
}

unsigned int			*llu_div(unsigned long long int n)
{
	unsigned int *res;

	res = (unsigned int *)malloc(sizeof(unsigned int) * 2);
	res[0] = n >> 32;
	n = n << 32;
	res[1] = n >> 32;
	return (res);
}

unsigned long long int	bl_ip(unsigned long long int n, char *ip)
{
	unsigned long long int	new;
	int						i;

	i = -1;
	new = 0;
	while (ip[++i])
	{
		new = new << 1;
		if ((n >> (64 - ip[i])) & 1)
			new |= 1;
	}
	return (new);
}

unsigned long long int	fin_ip(unsigned long long int n, char *fip)
{
	unsigned long long int	new;
	int						i;

	i = -1;
	new = 0;
	while (fip[++i])
	{
		new = new << 1;
		if ((n >> (64 - fip[i])) & 1)
			new |= 1;
	}
	return (new);
}
