# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 21:06:43 by yhwang            #+#    #+#              #
#    Updated: 2025/04/14 19:23:56 by yhwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = computor
NAME_BONUS = computor_bonus
CPP = c++

SRC_DIR = ./srcs/
INCS_DIR = ./incs/

CPPFLAGS = -Wall -Wextra -Werror -std=c++17 -g3

RM = rm -f

FILES = $(SRC_DIR)main \
		$(SRC_DIR)Parse/Parse \
		$(SRC_DIR)Parse/InputConvertor \
		$(SRC_DIR)Parse/SyntaxChecker \
		$(SRC_DIR)Parse/TermAnalyzer \
		$(SRC_DIR)Parse/BracketRemover \
		$(SRC_DIR)Parse/EquationSimplifier \
		$(SRC_DIR)Execute/Computor \
		$(SRC_DIR)Execute/LinearEquationSolver \
		$(SRC_DIR)Execute/QuadraticEquationSolver \
		$(SRC_DIR)Execute/SolutionStrGenerator \
		$(SRC_DIR)Execute/ExecuteUtils \
		$(SRC_DIR)MathUtils \
		$(SRC_DIR)Utils

SRCS = $(addsuffix .cpp, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

%.o: %.cpp $(INCS_DIR)
	$(CPP) $(CPPFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $^ -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS)
	$(CPP) $(CPPFLAGS) $^ -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
