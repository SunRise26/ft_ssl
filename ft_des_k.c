/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des_k.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:32:11 by vveselov          #+#    #+#             */
/*   Updated: 2018/03/01 19:28:43 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	key_hex_ch(char **key)
{
	int		i;

	if (!(*key))
		return ;
	i = 0;
	while ((*key)[i])
	{
		if ((*key)[i] >= 'a' && (*key)[i] <= 'f')
			(*key)[i] -= 32;
		if ((*key)[i] >= '0' && (*key)[i] <= '9')
			i++;
		else if ((*key)[i] >= 'A' && (*key)[i] <= 'F')
			i++;
		else
		{
			write(2, "non-hex digit\ninvalid hex key value\n", 36);
			free(*key);
			*key = NULL;
			return ;
		}
	}
}

void	key_er(char **key, int k)
{
	char	*new;
	int		i;

	i = 0;
	while ((*key)[i])
		i++;
	if (i > k)
		(*key)[k] = '\0';
	else if (i < k)
	{
		new = (char *)malloc(k + 1);
		i = -1;
		while ((*key)[++i])
			new[i] = (*key)[i];
		while (i < k)
			new[i++] = '0';
		new[k] = '\0';
		free(*key);
		*key = new;
	}
	key_hex_ch(key);
}

char	*ft_getp(char sw)
{
	char	s[20];
	char	*str;
	int		i;

	i = 0;
	if (sw == 0)
		readpassphrase("enter des key in hex: ", s, sizeof(s), RPP_FORCEUPPER);
	else if (sw == 1)
		readpassphrase("enter initial vector: ", s, sizeof(s), RPP_FORCEUPPER);
	while (s[i])
		i++;
	str = (char *)malloc(i + 1);
	i = -1;
	while (s[++i])
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}

char	*key_ch(int i, char **argv, char sw, int k)
{
	char	*res;
	int		j;

	j = 0;
	if (!i)
		res = ft_getp(sw);
	else
	{
		while (argv[i][j])
			j++;
		res = (char *)malloc(j + 1);
		j = -1;
		while (argv[i][++j])
			res[j] = argv[i][j];
		res[j] = '\0';
	}
	key_er(&res, k);
	return (res);
}
