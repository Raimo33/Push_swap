# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <craimond@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 12:26:33 by craimond          #+#    #+#              #
#    Updated: 2023/12/01 15:28:25 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
NAME_BONUS = checker
SRCS = $(addprefix srcs/mandatory/, push_swap.c a_to_b.c b_to_a.c stack_operations.c display.c general_utils.c lst_utils.c macros.c)
SRCS_BONUS = $(addprefix srcs/bonus/, checker_bonus.c stack_operations_bonus.c lst_utils_bonus.c general_utils_bonus.c $(addprefix get_next_line/, get_next_line.c get_next_line_utils.c))
HEADER = srcs/mandatory/push_swap.h
HEADER_BONUS = $(addprefix srcs/bonus/, checker_bonus.h get_next_line/get_next_line.h)
OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

.c.o:
	@cc -Wall -Wextra -Werror -c $< -o $@

${NAME}: ${OBJS} ${HEADER}
	@cc -Wall -Wextra -Werror ${OBJS} -o ${NAME}
	@echo compiled ${NAME}

${NAME_BONUS}: ${OBJS_BONUS} ${HEADER_BONUS}
	@cc -Wall -Wextra -Werror ${OBJS_BONUS} -o ${NAME_BONUS}
	@echo compiled ${NAME_BONUS}

all: ${NAME} ${NAME_BONUS}

bonus: ${NAME_BONUS}

clean:
	@rm -f ${OBJS} ${OBJS_BONUS}
	@echo removed obj files

fclean: clean
	@rm -f ${NAME} ${NAME_BONUS}
	@echo removed ${NAME} and ${NAME_BONUS} 

re: fclean all

.PHONY: all clean fclean re bonus