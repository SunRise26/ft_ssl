/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:40:18 by vveselov          #+#    #+#             */
/*   Updated: 2018/02/19 20:54:43 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void					ft_putstr(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

void					ft_puter(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	write(2, s, i);
}

void					ft_putstr_fd(unsigned char *s, int fd)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

int						ft_scmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

unsigned long long int	uint_join(unsigned int i1, unsigned int i2, int n)
{
	unsigned long long int	res;

	res = i1;
	res = res << n;
	i2 = i2 << (32 - n);
	i2 = i2 >> (32 - n);
	res |= i2;
	return (res);
}
