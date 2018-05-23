/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des3_cbc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 03:16:00 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/22 20:11:44 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	**des3_cbc_d(unsigned char **s1, char **s2, int *i, int a)
{
	char					**str;
	unsigned long long int	**key48;
	unsigned char			*buf;

	key48 = (unsigned long long **)malloc(sizeof(unsigned long long *) * 3);
	if (a)
	{
		buf = (unsigned char *)ft_base64d(s1, MIME, i);
		free(*s1);
		*s1 = buf;
	}
	str = ch_hex(*s1, HEXN, i);
	des3_key48(key48, s2);
	block3_cbc_d(str, key48, bl64(s2[1], HEXN));
	free(key48[0]);
	free(key48[1]);
	free(key48[2]);
	free(key48);
	free(*s1);
	*s1 = des_strj(str, *i);
	pad_ch(i, *s1);
	return (str);
}

char	**des3_cbc_e(unsigned char **s1, char **s2, int *i, int a)
{
	char					**str;
	unsigned long long int	**key48;
	unsigned char			*buf;

	key48 = (unsigned long long **)malloc(sizeof(unsigned long long *) * 3);
	str = ch_hex(*s1, HEXN, i);
	des3_key48(key48, s2);
	block3_cbc_e(str, key48, bl64(s2[1], HEXN));
	free(key48[0]);
	free(key48[1]);
	free(key48[2]);
	free(key48);
	free(*s1);
	*s1 = des_strj(str, *i);
	if (a)
	{
		buf = (unsigned char *)ft_base64e(s1, MIME, i);
		free(*s1);
		*s1 = buf;
	}
	return (str);
}

void	des3_cbc_m(int fd[7], char f, char **argv)
{
	char			**key;
	unsigned char	*s;
	char			**res;
	int				i;

	key = (char **)malloc(sizeof(char *) * 2);
	if (!(key[0] = key_ch(fd[4], argv, 0, 48)))
		return ;
	if (!(key[1] = key_ch(fd[6], argv, 1, 16)))
		return ;
	s = ft_read(fd[0], 8, &i);
	if (f == 0)
		s = des_pad(&s, &i);
	if (f == 0)
		res = des3_cbc_e(&s, key, &i, fd[5]);
	else
		res = des3_cbc_d(&s, key, &i, fd[5]);
	res_free(res);
	write(fd[2], s, i);
	free(s);
	free_cbc(key);
}

void	des3_cbc(char **argv)
{
	int		i;
	int		fd[7];
	char	f;

	f = 0;
	i = 1;
	fd[0] = 0;
	fd[2] = 1;
	fd[4] = 0;
	fd[5] = 0;
	fd[6] = 0;
	while (argv[++i])
		if (!ft_scmp(argv[i], "-e"))
			f = 0;
		else if (!ft_scmp(argv[i], "-d"))
			f = 1;
		else if (fd_iokiv(fd, argv, &i))
			;
		else
			des_cbc_options(argv[i]);
	if (file_er(fd, &fd[2], argv))
		return ;
	des3_cbc_m(fd, f, argv);
}
