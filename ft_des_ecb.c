/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des_ecb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:35:23 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/21 21:24:25 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned char	*hex_out(char *str, char *hex)
{
	unsigned char	c;
	unsigned char	*s;
	int				i;
	int				j;
	int				k;

	k = -1;
	i = -1;
	s = (unsigned char *)malloc(sizeof(char) * 9);
	s[8] = '\0';
	while (++i < 16)
	{
		j = 0;
		while (hex[j] && str[i] != hex[j])
			j++;
		c = j * 16;
		i++;
		j = 0;
		while (hex[j] && str[i] != hex[j])
			j++;
		c += j;
		s[++k] = c;
	}
	return (s);
}

void			des_ecb_options(char *s)
{
	if (s)
	{
		ft_puter("unknown option '");
		ft_puter(s);
		ft_puter("'\n");
	}
	ft_puter("options are\n-i <file>\tinput file\n\
-o <file>\toutput file\n-e\t\tencrypt\n-d\t\tdecrypt\n\
-a\t\tbase64 encode/decode\n-k\t\tkey in hex is the next argument\n");
	exit(0);
}

int				fd_iok(int fd[6], char **argv, int *i)
{
	int		j;

	j = 0;
	if (!ft_scmp(argv[*i], "-i") && ++j && argv[*i + 1] && (fd[1] = *i))
		fd[0] = open(argv[++(*i)], O_RDWR);
	else if (!ft_scmp(argv[*i], "-o") && ++j && argv[*i + 1] && (fd[3] = *i))
		fd[2] = open(argv[++(*i)], O_WRONLY | O_CREAT | O_TRUNC,
						S_IRWXU | S_IRWXG | S_IRWXO);
	else if (!ft_scmp(argv[*i], "-k") && ++j && argv[*i + 1])
		fd[4] = ++(*i);
	else if (!ft_scmp(argv[*i], "-a") && ++j)
		fd[5] = 1;
	else if (j)
		base64_options(NULL);
	else
		return (0);
	return (1);
}

void			des_ecb(char **argv)
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
	des_ecb_m(fd, f, argv);
}

void			des_ecb_m(int fd[6], char f, char **argv)
{
	char			*key;
	unsigned char	*s;
	char			**res;
	int				i;

	if (!(key = key_ch(fd[4], argv, 0, 16)))
		return ;
	s = ft_read(fd[0], 8, &i);
	if (f == 0)
		s = des_pad(&s, &i);
	if (f == 0)
		res = des_e(&s, key, &i, fd[5]);
	else
		res = des_d(&s, key, &i, fd[5]);
	write(fd[2], s, i);
	i = 0;
	while (res[i])
		free(res[i++]);
	free(res[i]);
	free(res);
	free(s);
	free(key);
}
