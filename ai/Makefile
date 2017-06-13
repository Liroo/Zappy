# Client

PROJECT := CLIENT

MK_DIR= ../mk/

OBJ_DIR := obj/

# General behavior

NAME_BIN := zappy_ai

SRC_GENDIR := src/
OBJ_GENDIR := $(OBJ_DIR)src/

SRC_GEN = \
	main.c

OBJ_GEN = $(addprefix $(OBJ_GENDIR), $(SRC_GEN:.c=.o))

# Utility

INCDIRS := -I./src

CC = gcc

FLAGS = -W -Werror -Wextra -Wall
# if debug is activated
FLAGS += $(DEBUG)
FLAGS += -D _GNU_SOURCE

CFLAGS = $(FLAGS) $(INCDIRS)

RM		:= rm -rf

include $(MK_DIR)colors.mk $(MK_DIR)defs.mk

# Rules

all:
	@make --no-print-directory $(NAME_BIN)

intro:
	@$(PRINTF) "$(YELLOW_R) ---- AI ---- $(CLEAR)\n"

# debug: FLAGS += -DDEBUG -g
debug: fclean
	@make --no-print-directory $(NAME_BIN) DEBUG='-DDEBUG -g'

$(OBJ_GENDIR)%.o: $(SRC_GENDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) -o $@ -c $< $(CFLAGS) $(ERRLOG)
	@$(PRINTF) "$(GREEN_R) $(ECHO) $(CLEAR) $<\n"

$(NAME_BIN): intro $(NAME_LIB) $(OBJ_GEN)
	@$(CC) -o $(NAME_BIN) $(OBJ_GEN) $(CFLAGS)
	@$(PRINTF) "$(GREEN_R) Done $(CLEAR)\n"

clean:
	@$(RM) $(OBJ_DIR)
	@$(PRINTF) "$(RED_R) Wiping...$(CLEAR) \n"

fclean:	clean
	@$(RM) $(NAME_BIN)
	@$(PRINTF) "$(RED_R) Brushing...$(CLEAR) \n"

re: fclean all

.PHONY: all debug $(NAME_BIN) clean fclean re debug
