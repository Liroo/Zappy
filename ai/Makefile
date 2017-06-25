##
## Makefile for  in /home/andre/reseau/Zappy/client
## 
## Made by andre
## Login   <andre@epitech.net>
## 
## Started on  Sat Jun 17 03:25:08 2017 andre
## Last update Sun Jun 25 21:21:32 2017 andre
##

PROJECT = ai

OBJ_DIR = obj/

# General behavior of arcade

NAME_BIN = zappy_ai

SRC_GENDIR = src/
OBJ_GENDIR = $(OBJ_DIR)src/

SRC_GEN = main.cpp \
	connection.cpp

OBJ_GEN = $(addprefix $(OBJ_GENDIR), $(SRC_GEN:.cpp=.o))

# Utility

INCDIRS := $(addprefix -I,$(shell find $(SRC_GENDIR) -type d -print)) -I./include/
CXX = g++
FLAGS = -W -Werror -Wextra -Wall
FLAGS += -std=c++14
FLAGS += $(DEBUG)
CXXFLAGS = $(FLAGS) $(INCDIRS)

RM		= rm -rf

# Rules

all:
	@make --no-print-directory $(NAME_BIN)

# debug: FLAGS += -DDEBUG -g
debug: fclean
	@make --no-print-directory $(NAME_BIN) DEBUG='-DDEBUG -g'

install:
	@make --no-print-directory

reinstall:
	@make --no-print-directory re

uninstall:
	@make --no-print-directory fclean

$(OBJ_GENDIR)%.o: $(SRC_GENDIR)%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

$(NAME_BIN): $(NAME_LIB) $(OBJ_GEN)
	$(CXX) -o $(NAME_BIN) $(OBJ_GEN) $(FLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME_BIN)

re: fclean all

.PHONY: debug
