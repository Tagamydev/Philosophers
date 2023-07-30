# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 19:28:25 by samusanc          #+#    #+#              #
#    Updated: 2023/07/30 19:46:21 by samusanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= aoeu
CFLAGS	= -Wall -Wextra -Werror -pthread -I ./
CC		= gcc $(CFLAGS)
THR		= gcc -Wall -Wextra -Werror -pthread -fsanitize=thread -I ./
LEAK	= gcc -Wall -Wextra -Werror -pthread -fsanitize=address -I ./
MAIN	= ./main.c
SRCS	= $(MAIN) \
		  ./ft_init_env.c \
		  ./ft_init_env_utils.c \
		  ./ft_free_env.c \

O_DIR	= ./objects/
OBJS	= $(addprefix $(O_DIR)/, $(SRCS:.c=.o))

$(O_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) -c $< -o $(O_DIR)/$(<:.c=.o)

all: $(NAME) $(SRCS)

thr: aoeu $(SRC)
	$(THR) ./main.c -o aoeu

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

re: fclean all

fclean: clean
	@rm -f $(NAME)

clean:
	@rm -f $(OBJS)

.PHONY: all
