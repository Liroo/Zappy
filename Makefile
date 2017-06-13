##
## Makefile<IRC> for IRC in /Users/pierre/Epitech/PSU/IRC
## 
## Made by Pierre Monge
## Login   <pierre@epitech.net>
## 
## Started on  Sat May 27 06:30:42 2017 Pierre Monge
## Last update Tue Jun 13 06:46:43 2017 Pierre Monge
##

PROJECT := IRC

SERVER = ./server
SERVER_BIN = zappy_server
CLIENT = ./ai
CLIENT_BIN = zappy_ai

CP = cp
RM = rm -f

all:
	@make --no-print-directory $(SERVER_BIN)
	@make --no-print-directory $(CLIENT_BIN)

$(SERVER_BIN):
	@make --no-print-directory -C $(SERVER)
	@$(CP) $(SERVER)/$(SERVER_BIN) .

$(CLIENT_BIN):
	@make --no-print-directory -C $(CLIENT)
	@$(CP) $(CLIENT)/$(CLIENT_BIN) .

debug:
	@make --no-print-directory -C $(SERVER_BIN) debug
	@make --no-print-directory -C $(CLIENT_BIN) debug
	@$(CP) $(SERVER)/$(SERVER_BIN) .
	@$(CP) $(CLIENT)/$(CLIENT_BIN) .

clean:
	@make --no-print-directory -C $(SERVER) clean
	@make --no-print-directory -C $(CLIENT) clean

fclean:
	@make --no-print-directory -C $(SERVER) fclean
	@make --no-print-directory -C $(CLIENT) fclean
	@$(RM) $(SERVER_BIN)
	@$(RM) $(CLIENT_BIN)

re: fclean all

.PHONY: debug
