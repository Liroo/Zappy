# Server

PROJECT := SERVER

MK_DIR= ../mk/

OBJ_DIR := obj/

# General behavior

NAME_BIN := zappy_server

SRC_GENDIR := src/
OBJ_GENDIR := $(OBJ_DIR)src/

SRC_GEN = \
	main.c \
	debug.c \
	sig.c \
	\
	list.c \
	fdlist.c \
	delete.c \
	map.c \
	chrono.c \
	\
	socket.c \
	bsd.c \
	r_packet.c \
	w_packet.c \
	dispatch.c \
	event.c \
	auth.c \
	\
	command.c \
	cmds/cmd_forward.c \
	cmds/cmd_left.c \
	cmds/cmd_right.c \
	cmds/cmd_take.c \
	cmds/cmd_connect_nbr.c \
	cmds/cmd_inventory.c \
	cmds/cmd_set.c \
	cmds/epur_str.c \
	cmds/parse_param.c \
	process.c \
	\
	parsing_option.c \
	option.c \
	name_option.c \
	\
	look.c \
	print_tiles.c \
	eject.c

OBJ_GEN = $(addprefix $(OBJ_GENDIR), $(SRC_GEN:.c=.o))

# Utility

INCDIRS := -I./include

CC = gcc

FLAGS = -W -Werror -Wextra -Wall
FLAGS += -D_GNU_SOURCE
# if debug is activated
FLAGS += $(DEBUG)

CFLAGS = $(FLAGS) $(INCDIRS)

RM		:= rm -rf

include $(MK_DIR)colors.mk $(MK_DIR)defs.mk

# Rules

all:
	@make --no-print-directory $(NAME_BIN) DEBUG='-DDEBUG=0'

intro:
	@$(PRINTF) "$(YELLOW_R) ---- SERVER ---- $(CLEAR)\n"
# debug: FLAGS += -DDEBUG -g
debug: fclean
	@make --no-print-directory $(NAME_BIN) DEBUG='-DDEBUG=1 -g'

$(OBJ_GENDIR)%.o: $(SRC_GENDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) -o $@ -c $< $(CFLAGS) $(ERRLOG)
	@$(PRINTF) "$(GREEN_R)$(ECHO) $(CLEAR)\t$<\n"

$(NAME_BIN): intro $(OBJ_GEN)
	@$(CC) -o $(NAME_BIN) $(OBJ_GEN) $(CFLAGS)
	@$(PRINTF) "$(GREEN_R)Done $(CLEAR)\n"

clean:
	@$(RM) $(OBJ_DIR)
	@$(PRINTF) "$(RED_R)Cleaning...$(CLEAR) \n"

fclean:	clean
	@$(RM) $(NAME_BIN)
	@$(PRINTF) "$(RED_R)Dusting...$(CLEAR) \n"

re: fclean all

.PHONY: all debug $(NAME_BIN) clean fclean re debug
