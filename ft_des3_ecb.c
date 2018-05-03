/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des3_ecb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:58:44 by vveselov          #+#    #+#             */
/*   Updated: 2018/03/02 10:27:07 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			des3_ecb_e(unsigned char **s, char *key, int *i, int a)
{
	char	**res;
	int		sw;

	res = des_e(s, &key[0], i, 0);
	res_free(res);
	sw = *i;
	res = des_d(s, &key[16], i, 0);
	res_free(res);
	*i = sw;
	res = des_e(s, &key[32], i, a);
	res_free(res);
}

void			des3_ecb_d(unsigned char **s, char *key, int *i, int a)
{
	char	**res;

	res = des_d(s, &key[32], i, a);
	res_free(res);
	res = des_e(s, &key[16], i, 0);
	res_free(res);
	res = des_d(s, &key[0], i, 0);
	res_free(res);
}

void			des3_ecb_m(int fd[6], char f, char **argv)
{
	char			*key;
	unsigned char	*s;
	int				i;

	if (!(key = key_ch(fd[4], argv, 0, 48)))
		return ;
	s = ft_read(fd[0], 8, &i);
	if (f == 0)
		s = des_pad(&s, &i);
	if (f == 0)
		des3_ecb_e(&s, key, &i, fd[5]);
	else
		des3_ecb_d(&s, key, &i, fd[5]);
	write(fd[2], s, i);
	free(s);
	free(key);
}

void			des3_ecb(char **argv)
{
	int		i;
	int		fd[6];
	char	f;

	f = 0;
	i = 1;
	fd[0] = 0;
	fd[2] = 1;
	fd[4] = 0;
	fd[5] = 0;
	while (argv[++i])
		if (!ft_scmp(argv[i], "-e"))
			f = 0;
		else if (!ft_scmp(argv[i], "-d"))
			f = 1;
		else if (fd_iok(fd, argv, &i))
			;
		else
			des_ecb_options(argv[i]);
	if (file_er(fd, &fd[2], argv))
		return ;
	des3_ecb_m(fd, f, argv);
}
