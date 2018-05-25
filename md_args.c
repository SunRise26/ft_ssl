/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 17:26:22 by vveselov          #+#    #+#             */
/*   Updated: 2018/05/25 17:11:48 by vveselov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	md_options(char *s)
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

void	md_out(char *out, int flags, char *md_str, char *md_name)
{
	if (flags & 2)
		ft_putendl(out);
	else if (!(flags & 4))
	{
		ft_toupper(md_name);
		ft_putstr(md_name);
		write(1, " (", 2);
		ft_putstr(md_str);
		write(1, ") = ", 4);
		ft_putendl(out);
	}
	else
	{
		ft_putstr(out);
		write(1, " ", 1);
		ft_putendl(md_str);
	}
	if (!(flags & 32))
		free(md_str);
	free(out);
}

void	md_files(int flags, char **argv, int i,
				char *(*md_e)(char *argv))
{
	int		fd[4];
	char	*str;
	int		len;

	fd[2] = 1;
	fd[3] = 0;
	len = -1;
	while (argv[i])
	{
		fd[0] = open(argv[i], O_RDONLY);
		fd[1] = i - 1;
		if (!file_er(fd, &fd[2], argv))
		{
			str = (char *)ft_read(fd[0], 8, &len);
			close(fd[0]);
			md_out(md_e(str), (flags | 32), argv[i], argv[1]);
			free(str);
		}
		i++;
	}
}

void	md_stdin(int *flags, char *(*md_e)(char *argv), char *md_name)
{
	char	*str;
	int		len;

	len = 0;
	str = NULL;
	if (!(*flags & 1))
	{
		str = (char *)ft_read(0, 8, &len);
		*flags |= 1;
	}
	if (!(*flags & 16))
		write(1, str, len);
	if (str)
	{
		md_out(md_e(str), 2, NULL, md_name);
		free(str);
	}
}

void	md_main(char **argv, char *(*md_e)(char *argv))
{
	int		i;
	int		flags;

	i = 1;
	flags = 0;
	while (argv[++i] && argv[i][0] == '-')
		if (argv[i][1] == 'p')
			md_stdin(&flags, md_e, argv[1]);
		else if (argv[i][1] == 'q')
			flags |= 2;
		else if (argv[i][1] == 'r')
			flags |= 4;
		else if (argv[i][1] == 's' && argv[++i])
		{
			flags |= 8;
			md_out(md_e(argv[i]), flags, word_in_br(argv[i]), argv[1]);
		}
		else
			md_options(argv[i]);
	if (!argv[i] && !(flags & 1) && !(flags & 8))
	{
		flags |= 16;
		md_stdin(&flags, md_e, argv[1]);
	}
	md_files(flags, argv, i, md_e);
}
