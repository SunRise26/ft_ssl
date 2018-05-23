# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vveselov <vveselov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/17 17:27:16 by vveselov          #+#    #+#              #
#    Updated: 2018/05/23 17:32:02 by vveselov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

OBJ_DIR = ./

SRC_DIR = ./

INC_DIR = ./

SRC = des3_cbc_e.c des_cbc_ed.c ft_base64.c ft_base64ed.c ft_base64wh.c \
ft_conv.c ft_des3_cbc.c ft_des3_ecb.c ft_des_cbc.c ft_des_d.c ft_des_e.c \
ft_des_ecb.c ft_des_k.c ft_des_key.c ft_des_other.c ft_main_other.c \
ft_perm.c ft_ssl.c min_lib.c md5_e.c md5_proc.c md5_bwise_fun.c\
sha256_e.c sha256_proc.c bit_sh.c sha256_bwise.c md_args.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

$(OBJ_DIR)%.o: %.c
	gcc -c $< -o $@ $(CFLAGS) -I $(INC_DIR)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

vpath %.c $(SRC_DIR)
