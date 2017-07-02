##
## Makefile<IRC> for IRC in /Users/pierre/Epitech/PSU/IRC
## 
## Made by Pierre Monge
## Login   <pierre@epitech.net>
## 
## Started on  Sat May 27 06:30:42 2017 Pierre Monge
## Last update Sun Jul  2 23:28:16 2017 Thomas
##

PROJECT := IRC

SERVER = ./server
SERVER_BIN = zappy_server
AI = ./ai
AI_BIN = zappy_ai
ADMIN = ./admin
ADMIN_BIN = zappy_admin
CLIENT = ./client
CLIENT_BIN = zappy_client

CP = cp
RM = rm -f

all:
	@make --no-print-directory $(SERVER_BIN)
	@make --no-print-directory $(AI_BIN)
	@make --no-print-directory $(ADMIN_BIN)
	@make --no-print-directory $(CLIENT_BIN)

$(SERVER_BIN):
	@make --no-print-directory -C $(SERVER)
	@$(CP) $(SERVER)/$(SERVER_BIN) .

$(AI_BIN):
	@make --no-print-directory -C $(AI)
	@$(CP) $(AI)/$(AI_BIN) .

$(ADMIN_BIN):
	@make --no-print-directory -C $(ADMIN)
	@$(CP) $(ADMIN)/$(ADMIN_BIN) .

$(CLIENT_BIN):
	@make --no-print-directory -C $(CLIENT)
	@$(CP) $(CLIENT)/$(CLIENT_BIN) .

debug:
	@make --no-print-directory -C $(SERVER) debug
	@make --no-print-directory -C $(AI) debug
	@make --no-print-directory -C $(ADMIN) debug
	@make --no-print-directory -C $(CLIENT) debug
	@$(CP) $(SERVER)/$(SERVER_BIN) .
	@$(CP) $(AI)/$(AI_BIN) .
	@$(CP) $(ADMIN)/$(ADMIN_BIN) .
	@$(CP) $(CLIENT)/$(CLIENT_BIN) .

clean:
	@make --no-print-directory -C $(SERVER) clean
	@make --no-print-directory -C $(AI) clean
	@make --no-print-directory -C $(ADMIN) clean
	@make --no-print-directory -C $(CLIENT) clean

fclean:
	@make --no-print-directory -C $(SERVER) fclean
	@make --no-print-directory -C $(AI) fclean
	@make --no-print-directory -C $(ADMIN) fclean
	@make --no-print-directory -C $(CLIENT) fclean
	@$(RM) $(SERVER_BIN)
	@$(RM) $(AI_BIN)
	@$(RM) $(ADMIN_BIN)
	@$(RM) $(CLIENT_BIN)

re: fclean all

.PHONY: $(SERVER_BIN) $(AI_BIN) $(ADMIN_BIN) $(CLIENT_BIN) debug clean fclean re
