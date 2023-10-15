# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 19:28:25 by samusanc          #+#    #+#              #
#    Updated: 2023/10/15 17:41:40 by samusanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CFLAGS	= -Wall -Wextra -Werror -pthread -I ./ #-g3 -fsanitize=thread
CC		= gcc $(CFLAGS)
THR		= gcc -Wall -Wextra -Werror -pthread -fsanitize=thread -I ./
LEAK	= gcc -Wall -Wextra -Werror -pthread -fsanitize=address -I ./
MAIN	= ./main.c
SRCS	= $(MAIN) \
		  ./u_forks.c \
		  ./l_forks.c \
		  ./eat.c \
		  ./start_sim.c \
		  ./ft_atoui.c \
		  ./m_free.c \
		  ./free_all.c \
		  ./fill_numbers_philo.c \
		  ./alloc_init.c \
		  ./mutex_save.c \
		  ./array_save.c \
		  ./init_philo.c \
		  ./death.c \
		  ./ft_sleep.c \
		  ./tmp.c \
		  ./time.c \
		  ./routine.c \

O_DIR	= ./objects/
OBJS	= $(addprefix $(O_DIR)/, $(SRCS:.c=.o))

$(O_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) -c $< -o $(O_DIR)/$(<:.c=.o)


O_DIR	= ./objects/
OBJS	= $(addprefix $(O_DIR)/, $(SRCS:.c=.o))

$(O_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) -c $< -o $(O_DIR)/$(<:.c=.o)

all: $(NAME) $(SRCS)

thr: minishell $(SRC)
	$(THR) ./main.c -o aoeu

leak: minishell $(SRC)
	$(LEAK) ./main.c -o minishell

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

re: fclean all

fclean: clean
	@rm -f $(NAME)

clean:
	@rm -f $(OBJS)

.PHONY: all
