/*
** struct.h for struct in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 13 12:00:23 2017 Pierre Monge
** Last update Tue Jun 13 21:35:39 2017 Pierre Monge
*/

#ifndef STRUCT_H
# define STRUCT_H

# include "list.h"

typedef enum	e_stone
  {
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    UNKNOWN = -1
  }		t_stone;

typedef struct	s_tiles		t_tiles;
typedef struct	s_player	t_player;
typedef struct	s_team		t_team;
typedef struct	s_inventory	t_inventory;
typedef struct	s_game		t_game;

struct		s_inventory
{
  unsigned int 	linemate;
  unsigned int 	deraumere;
  unsigned int 	sibur;
  unsigned int 	mendiane;
  unsigned int 	phiras;
  unsigned int 	thystame;
  unsigned int	food;
};

struct		s_tiles
{
  t_inventory	inventory;
};

struct		s_player
{
  int		pos_x;
  int		pos_y;

  unsigned char	elevation;
  t_inventory	inventory;
  t_list_head	list;
};

struct		s_team
{
  t_list_head	players;

  int		size;
  int		empty_slot;
  t_list_head	list;
};

struct		s_game
{
  unsigned int	map_size_x;
  unsigned int	map_size_y;
  t_inventory	**map;

  t_list_head	teams;
  unsigned int	nb_client_max;
  int		time;
};

#endif /* !STRUCT_H */
