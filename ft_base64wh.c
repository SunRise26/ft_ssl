/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64wh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 17:08:43 by vveselov          #+#    #+#             */
/*   Updated: 2018/03/02 14:52:59 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		ft_whsp(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' ||
		c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	ft_base64wh(unsigned char **in, int i)
{
	int				j;
	int				k;
	int				ct;
	unsigned char	*new;

	j = -1;
	ct = 0;
	while ((*in)[++j])
		if (ft_whsp((*in)[j]))
			ct++;
	if (ct)
	{
		new = (unsigned char *)malloc(i - ct + 1);
		j = -1;
		k = 0;
		while ((*in)[++j])
			if (!ft_whsp((*in)[j]))
				new[k++] = (*in)[j];
		new[k] = '\0';
		free(*in);
		*in = new;
	}
}
