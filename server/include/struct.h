/*
** struct.h for struct in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 13 12:00:23 2017 Pierre Monge
** Last update Tue Jun 20 22:38:52 2017 Pierre Monge
*/

#ifndef STRUCT_H
# define STRUCT_H

# include "list.h"

typedef struct	s_tiles		t_tiles;
typedef struct	s_player	t_player;
typedef struct	s_team		t_team;
typedef struct	s_inventory	t_inventory;
typedef struct	s_game		t_game;
typedef struct	s_net_info	t_net_info;

struct		s_net_info
{
  int		fd;
  int		port;
};

struct		s_inventory
{
  unsigned int 	linemate;
  unsigned int 	deraumere;
  unsigned int 	sibur;
  unsigned int 	mendiane;
  unsigned int 	phiras;
  unsigned int 	thystame;
  unsigned int	food;

  /*
  ** if inventory is in reality a case of the map
  */
  unsigned int	player;
};

# define LINEMATE_OFFSET offsetof(t_inventory, linemate)
# define MIN_LINEMATE_PER_TEAM 54 + (54 / 2)
# define DERAUMERE_OFFSET offsetof(t_inventory, deraumere)
# define MIN_DERAUMERE_PER_TEAM 48 + (48 / 2)
# define SIBUR_OFFSET offsetof(t_inventory, sibur)
# define MIN_SIBUR_PER_TEAM 60 + (60 / 2)
# define MENDIANE_OFFSET offsetof(t_inventory, mendiane)
# define MIN_MENDIANE_PER_TEAM 30 + (30 / 2)
# define PHIRAS_OFFSET offsetof(t_inventory, phiras)
# define MIN_PHIRAS_PER_TEAM 36 + (36 / 2)
# define THYSTAME_OFFSET offsetof(t_inventory, thystame)
# define MIN_THYSTAME_PER_TEAM 6 + (6 / 2)
# define FOOD_OFFSET offsetof(t_inventory, food)
# define PLAYER_OFFSET offsetof(t_inventory, player)
# define INSERT_OBJECT(inventory, offset) *(((char *)inventory) + offset) += 1
# define REMOVE_OBJECT(inventory, offset) *(((char *)inventory) + offset) -= 1

struct		s_tiles
{
  t_inventory	inventory;
};

# include "command.h"
# define COMMAND_QUEUE_SIZE 10
# include "packet.h"

struct			s_player
{
  char			is_logged;

  int			pos_x;
  int			pos_y;
  int			direction;

  unsigned char		elevation;
  t_inventory		inventory;
  t_list_head		list;
  t_team		*team;

  int			command_in_queue;
  t_command_queue	command_queue[COMMAND_QUEUE_SIZE];
  t_packet		r_packet;
  t_list_head		w_packet;
  t_net_info		net_info;
};

struct		s_team
{
  t_list_head	players;

  char		*name;
  int		size;
  int		empty_slot;
  t_list_head	list;
};

# include "event.h"

struct		s_game
{
  unsigned int	map_size_x;
  unsigned int	map_size_y;
  t_inventory	**map;

  t_list_head	teams;
  unsigned int	nb_client_max;
  int		time;

  t_list_head	connection_queue;
  t_net_info	net_info;
  int		sig_handled;
};

extern t_game	game;

#endif /* !STRUCT_H */
