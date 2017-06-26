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
	log.c \
	exit.c \
	\
	socket.c \
	bsd.c \
	r_packet.c \
	w_packet.c \
	dispatch.c \
	fdevent.c \
	auth.c \
	\
	list.c \
	fdlist.c \
	map.c \
	\
	parsing_option.c \
	option.c \
	name_option.c \
	\
	chrono/chrono.c \
	chrono/c_operator.c \
	chrono/c_delete.c \
	\
	delete/d_client.c \
	delete/d_team.c \
	delete/d_game.c \
	\
	event/e_command.c \
	event/e_lifetime.c \
	event/e_timeout.c \
	\
	command.c \
	command_list.c \
	process.c \
	\
	command/command_forward.c \
	command/command_left.c \
	command/command_right.c \
	command/command_connect_nbr.c \
	command/command_look.c \
	command/print_tiles.c \
	command/command_inventory.c \
	command/command_set.c \
	command/command_take.c \
	command/strepur.c \
	command/parse.c \
	command/command_broadcast.c \
	command/algorithme_vector.c \
	command/config_algorithme.c \
	command/get_max_value.c \
	command/command_eject.c


OBJ_GEN = $(addprefix $(OBJ_GENDIR), $(SRC_GEN:.c=.o))

# Utility

INCDIRS := -I./include

CC = gcc -g

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
