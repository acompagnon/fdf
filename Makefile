# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acompagn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/01 17:56:14 by acompagn          #+#    #+#              #
#    Updated: 2019/03/16 16:18:03 by acompagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

DIR_SRCS =	srcs
SRCS = 		main.c \
	   		sort_input.c \
			malloc_free.c \
			init.c \
			hooks.c \
			draw.c \
			menu.c \
			move_restart.c \
			camera.c \

FDF_SRCS = $(patsubst %,$(DIR_SRCS)/%,$(SRCS))

DIR_OBJ = obj
FDF_OBJ = $(patsubst %,$(DIR_OBJ)/%,$(SRCS:.c=.o))
LIBFT = libft/libft.a

CFLAGS = -Wall -Werror -Wextra

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
CYAN = \033[36m
END= \033[0m

.PHONY: clean fclean all re libft

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft

$(DIR_OBJ):
	@mkdir -p $@

$(FDF_OBJ): obj%.o : $(DIR_SRCS)%.c inc/fdf.h
	@gcc $(CFLAGS) -c $< -o $@ -Iinc -Ilibft
	@printf "\e[2K \e[32m[CC]\e[0m %-15s\r" "$<"

$(NAME): $(DIR_OBJ) $(FDF_OBJ)
	@gcc $(CFLAGS) $(FDF_OBJ) -o $@  -I libft -L libft/ -lft -lmlx -framework OpenGL -framework Appkit
	@printf "\n\e[2k\e[32m[PRG]\e[0m $(NAME) done\n"

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
