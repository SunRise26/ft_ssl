/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:33:41 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/22 20:16:02 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	base64_options(char *s)
{
	if (s)
	{
		ft_puter("unknown option '");
		ft_puter(s);
		ft_puter("'\n");
	}
	ft_puter("options are\n-i <file>\tinput file\n\
-o <file>\toutput file\n-e\t\tencrypt\n-d\t\tdecrypt\n");
	exit(0);
}

void	base64_m(int fd_i, int fd_o, char f)
{
	unsigned char	*in;
	unsigned char	*res;
	int				len;
	char			*(*func)(unsigned char **, char *, int *);
	int				i;

	func = NULL;
	if (f == 0 && (len = 3))
		func = ft_base64e;
	else if (f == 1 && (len = 4))
		func = ft_base64d;
	in = ft_read(fd_i, len, &i);
	if (fd_i != 0)
		close(fd_i);
	res = (unsigned char *)func(&in, MIME, &i);
	write(fd_o, res, i);
	if (fd_o != 1)
		close(fd_o);
	free(in);
	free(res);
}

int		fd_io(int fd_i[2], int fd_o[2], char **argv, int *i)
{
	if (!ft_scmp(argv[*i], "-i") && argv[*i + 1] && (fd_i[1] = *i))
		fd_i[0] = open(argv[++(*i)], O_RDONLY);
	else if (!ft_scmp(argv[*i], "-o") && argv[*i + 1] && (fd_o[1] = *i))
		fd_o[0] = open(argv[++(*i)], O_WRONLY | O_CREAT | O_TRUNC,
						S_IRWXU | S_IRWXG | S_IRWXO);
	else if (!ft_scmp(argv[*i], "-i") || !ft_scmp(argv[*i], "-o"))
		base64_options(NULL);
	else
		return (0);
	return (1);
}

void	base64(char **argv)
{
	int		i;
	int		fd_i[2];
	int		fd_o[2];
	char	f;

	f = 0;
	i = 1;
	fd_i[0] = 0;
	fd_o[0] = 1;
	while (argv[++i])
		if (!ft_scmp(argv[i], "-e"))
			f = 0;
		else if (!ft_scmp(argv[i], "-d"))
			f = 1;
		else if (fd_io(fd_i, fd_o, argv, &i))
			;
		else
			base64_options(argv[i]);
	if (file_er(fd_i, fd_o, argv))
		return ;
	base64_m(fd_i[0], fd_o[0], f);
}
