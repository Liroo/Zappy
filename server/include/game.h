/*
** game.h for game in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Wed Jun 21 04:15:36 2017 Pierre Monge
** Last update Sat Jul  1 03:47:10 2017 Pierre Monge
*/

#ifndef GAME_H
# define GAME_H

# define ADMIN_TEAM "admin"
# define ADMIN_TEAM_PASSWD "admin"
# define SPECTATOR_TEAM "spectator"
# define SPECTATOR_TEAM_PASSWD "spectator"

# define MIN_LINEMATE_PER_TEAM 54 + (54 / 2)
# define MIN_DERAUMERE_PER_TEAM 48 + (48 / 2)
# define MIN_SIBUR_PER_TEAM 60 + (60 / 2)
# define MIN_MENDIANE_PER_TEAM 30 + (30 / 2)
# define MIN_PHIRAS_PER_TEAM 36 + (36 / 2)
# define MIN_THYSTAME_PER_TEAM 6 + (6 / 2)

# define N	1
# define NW	2
# define W	3
# define SW	4
# define S	5
# define SE	6
# define E	7
# define NE	8

# define COMMAND_QUEUE_SIZE 10
# define AUTH_TIMEOUT(f) 10 * f

# define LIFETIME_WITHOUT_FOOD 126
# define DFL_FOOD_START 9

# define CHRONO_FORWARD	7
# define CHRONO_RIGHT 7
# define CHRONO_LEFT 7
# define CHRONO_LOOK 7
# define CHRONO_INVENTORY 1
# define CHRONO_BROADCAST 7
# define CHRONO_FORK 42
# define CHRONO_EJECT 7
# define CHRONO_TAKE 7
# define CHRONO_SET 7
# define CHRONO_INCANTATION 300

# define RPL_OK "ok\n"
# define RPL_KO "ko\n"

# define RPL_TIMEOUT "timeout\n"
# define RPL_WELCOME "WELCOME\n"
# define RPL_PASSWD "Require password\n"
# define RPL_WRONG_PASSWD "Wrong password\n"
# define RPL_DEAD "dead\n"

#endif /* !GAME_H */
