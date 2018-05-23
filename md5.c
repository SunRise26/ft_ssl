/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:39:01 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/23 12:40:35 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	md5_options(char *s)
{
	if (s)
	{
		ft_puter("unknown option '");
		ft_puter(s);
		ft_puter("'\n");
	}
	ft_puter("options are\n-p\t\techo STDIN to STDOUT and append the\
checksum to STDOUT\n-q\t\tquiet mode\n-r\t\treverse the format of the output\n\
-s <string>\tprint the sum of the given string\n");
	exit(0);
}

void	md5_out(char *out, int flags, char *md5_str)
{
	if (flags & 2)
	{
		ft_putendl(out);
		return ;
	}
	if (!(flags & 4))
	{
		write(1, "MD5 (", 5);
		ft_putstr(md5_str);
		write(1, ") = ", 4);
		ft_putendl(out);
	}
	else
	{
		ft_putstr(out);
		write(1, " ", 1);
		ft_putendl(md5_str);
	}
	if (flags & 8)
		free(md5_str);
	free(out);
}

void	md5_files(int flags, char **argv, int i)
{
	int		fd[4];
	char	*str;
	int		len;

	fd[2] = 1;
	fd[3] = 0;
	len = 0;
	while (argv[i])
	{
		fd[0] = open(argv[i], O_RDONLY);
		fd[1] = i - 1;
		if (!file_er(fd, &fd[2], argv))
		{
			str = (char *)ft_read(fd[0], 8, &len);
			close(fd[0]);
			md5_out(md5_e(str), flags, argv[i]);
			free(str);
		}
		i++;
	}
}

void	md5_stdin(int *flags)
{
	char	*str;
	int		len;

	len = 0;
	str = NULL;
	if (!(*flags & 1))
		str = (char *)ft_read(0, 8, &len);
	write(1, str, len);
	md5_out(md5_e(str), 2, NULL);
	free(str);
	*flags |= 1;
}

void	md5(char **argv)
{
	int		i;
	int		flags;

	i = 1;
	flags = 0;
	while (argv[++i] && argv[i][0] == '-')
		if (argv[i][1] == 'p')
			md5_stdin(&flags);
		else if (argv[i][1] == 'q')
			flags |= 2;
		else if (argv[i][1] == 'r')
			flags |= 4;
		else if (argv[i][1] == 's' && argv[++i])
			md5_out(md5_e(argv[i]), (flags | 8), word_in_br(argv[i]));
		else
			md5_options(argv[i]);
	md5_files(flags, argv, i);
}
