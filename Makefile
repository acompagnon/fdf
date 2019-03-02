# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acompagn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/01 17:56:14 by acompagn          #+#    #+#              #
#    Updated: 2019/03/02 16:19:35 by acompagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

DIR_SRCS =	srcs
SRCS = 		main.c \
	   		sort_input.c \
			free.c \
			init.c \
			print.c \
			mlx.c \

FDF_SRCS = $(patsubst %,$(DIR_SRCS)/%,$(SRCS))

DIR_OBJ = obj
FDF_OBJ = $(patsubst %,$(DIR_OBJ)/%,$(SRCS:.c=.o))
LIBFT = libft/libft.a

CFLAGS = -Wall -Werror -Wextra -g3

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
CYAN = \033[36m
END= \033[0m

.PHONY: clean fclean all re libft

all: $(NAME)

$(LIBFT):
	@make -C libft

$(DIR_OBJ):
	@mkdir -p $@

$(FDF_OBJ): obj%.o : $(DIR_SRCS)%.c
	@gcc $(CFLAGS) -c $< -o $@ -Iinc -Ilibft
	@printf "\e[2K \e[32m[CC]\e[0m %-15s\r" "$<"

$(NAME): $(DIR_OBJ) $(FDF_OBJ) $(LIBFT)
	@gcc $(CFLAGS) $(FDF_OBJ) -o $@  -I libft -L libft/ -lft -lmlx -framework OpenGL -framework Appkit
	@printf "\033[32m[PRG]\e[0m $(NAME) done\n"


clean:
	@/bin/rm -rf $(DIR_OBJ)
	@make clean -C libft
	@echo "$(GREEN)[OK]$(END) Clean fdf objects"

fclean:
	@/bin/rm -rf $(DIR_OBJ)
	@/bin/rm -f $(NAME)
	@make fclean -C libft
	@echo "$(GREEN)[OK]$(END) Delete fdf"

re: fclean all
