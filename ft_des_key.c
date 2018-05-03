/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:29:20 by vveselov          #+#    #+#             */
/*   Updated: 2018/02/19 19:38:04 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int		*pc_one(unsigned long long int n, char *pc1)
{
	unsigned long long int	new;
	unsigned int			*res;
	int						i;

	i = -1;
	new = 0;
	while (pc1[++i])
	{
		new = new << 1;
		if ((n >> (64 - pc1[i])) & 1)
			new |= 1;
	}
	res = (unsigned int *)malloc(sizeof(unsigned int) * 2);
	res[0] = new >> 28;
	new = new << 36;
	res[1] = new >> 36;
	return (res);
}

unsigned int		lsh1(unsigned int n)
{
	char			c;
	unsigned int	res;

	c = (n >> 27) & 1;
	res = n << 1;
	if (c)
		res |= 1;
	return (res);
}

unsigned int		*lshift(unsigned int *n)
{
	unsigned int	*res;
	int				i;
	int				k;

	i = 0;
	res = (unsigned int *)malloc(sizeof(unsigned int) * 33);
	res[32] = 0;
	res[0] = lsh1(n[0]);
	res[1] = lsh1(n[1]);
	k = 2;
	while (++i < 16)
	{
		res[k] = lsh1(res[k - 2]);
		res[k + 1] = lsh1(res[k - 1]);
		if (i != 1 && i != 8 && i != 15)
		{
			res[k] = lsh1(res[k]);
			res[k + 1] = lsh1(res[k + 1]);
		}
		k += 2;
	}
	return (res);
}

unsigned long long	*pc_two(unsigned int *key16, char *pc2)
{
	unsigned long long int	*res;
	unsigned long long int	new;
	int						i;
	int						j;
	int						k;

	j = -1;
	k = -1;
	res = (unsigned long long int *)malloc(sizeof(unsigned long long int) * 16);
	while (++k < 16)
		res[k] = 0;
	k = 0;
	while (++j < 16)
	{
		i = -1;
		new = uint_join(key16[k], key16[k + 1], 28);
		k += 2;
		while (pc2[++i])
		{
			res[j] = res[j] << 1;
			if ((new >> (56 - pc2[i])) & 1)
				res[j] |= 1;
		}
	}
	return (res);
}
