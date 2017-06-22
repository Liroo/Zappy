/*
** game.h for game in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Wed Jun 21 04:15:36 2017 Pierre Monge
** Last update Fri Jun 23 00:58:42 2017 Pierre Monge
*/

#ifndef GAME_H
# define GAME_H

# define MIN_LINEMATE_PER_TEAM 54 + (54 / 2)
# define MIN_DERAUMERE_PER_TEAM 48 + (48 / 2)
# define MIN_SIBUR_PER_TEAM 60 + (60 / 2)
# define MIN_MENDIANE_PER_TEAM 30 + (30 / 2)
# define MIN_PHIRAS_PER_TEAM 36 + (36 / 2)
# define MIN_THYSTAME_PER_TEAM 6 + (6 / 2)

# define COMMAND_QUEUE_SIZE 10
# define AUTH_TIMEOUT(f) 10 * f

# define LIFETIME_WITHOUT_FOOD 126

# define RPL_OK "ok\n"
# define RPL_KO "ko\n"

# define RPL_TIMEOUT "timeout\n"
# define RPL_WELCOME "WELCOME\n"
# define RPL_DEAD "dead\n"

#endif /* !GAME_H */
