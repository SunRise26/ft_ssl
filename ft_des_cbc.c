/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des_cbc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:12:41 by vveselov          #+#    #+#             */
/*   Updated: 2018/03/02 10:26:55 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			des_cbc_options(char *s)
{
	if (s)
	{
		ft_puter("unknown option '");
		ft_puter(s);
		ft_puter("'\n");
	}
	ft_puter("options are\n-i <file>\tinput file\n\
-o <file>\toutput file\n-e\t\tencrypt\n-d\t\tdecrypt\n\
-a\t\tbase64 encode/decode\n-k/-v\t\tkey/iv in hex is the next argument\n");
	exit(0);
}

int				fd_iokiv(int fd[7], char **argv, int *i)
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
	else if (!ft_scmp(argv[*i], "-v") && ++j && argv[*i + 1])
		fd[6] = ++(*i);
	else if (!ft_scmp(argv[*i], "-a") && ++j)
		fd[5] = 1;
	else if (j)
		base64_options(NULL);
	else
		return (0);
	return (1);
}

void			free_cbc(char **key)
{
	free(key[0]);
	free(key[1]);
	free(key);
}

void			des_cbc_m(int fd[7], char f, char **argv)
{
	char			**key;
	unsigned char	*s;
	char			**res;
	int				i;

	key = (char **)malloc(sizeof(char *) * 2);
	if (!(key[0] = key_ch(fd[4], argv, 0, 16)))
		return ;
	if (!(key[1] = key_ch(fd[6], argv, 1, 16)))
		return ;
	s = ft_read(fd[0], 8, &i);
	if (f == 0)
		s = des_pad(&s, &i);
	if (f == 0)
		res = des_cbc_e(&s, key, &i, fd[5]);
	else
		res = des_cbc_d(&s, key, &i, fd[5]);
	write(fd[2], s, i);
	free(s);
	i = 0;
	while (res[i])
		free(res[i++]);
	free(res[i]);
	free(res);
	free_cbc(key);
}

void			des_cbc(char **argv)
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
	des_cbc_m(fd, f, argv);
}
