/*
** process.c for process in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Wed Jun 21 04:30:29 2017 Pierre Monge
** Last update Sat Jun 24 20:48:13 2017 Pierre Monge
*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "struct.h"
#include "list.h"
#include "chrono.h"
#include "h.h"
#include "debug.h"

void			process_chrono_event()
{
  t_list_head		*pos;
  t_list_head		*next;
  t_chrono_queue	now;
  t_chrono_queue	*container;
  t_chrono_event_func	*chrono_event_func_list;

  pos = list_get_first(&game.chrono_queue);
  memset(&now, 0, sizeof(t_chrono_queue));
  if (clock_gettime(CLOCK_REALTIME, &now.end) == -1)
    perror("clock_gettime");
  chrono_event_func_list = get_chrono_event_func_list();
  while (pos != &game.chrono_queue)
    {
      next = pos->next;
      container = list_entry(pos, t_chrono_queue, list);
      if (compare_time(container->end, now.end) <= 0)
	{
	  chrono_event_func_list[container->event_type](container->data);
	  delete_chrono(container);
	}
      else
	container->duration = sub_time(container->end, now.end);
      pos = next;
    }
}

static void	process_player(t_player *player)
{
  int		i;

  if (player->command_is_running || player->command_in_queue <= 0)
    return ;
  (*player->command_queue).exec(player, (*player->command_queue).command);
  free((*player->command_queue).command);
  (*player->command_queue).command = NULL;
  i = 0;
  while (i < player->command_in_queue)
    {
      player->command_queue[i] = player->command_queue[i + 1];
      i++;
    }
  player->command_in_queue -= 1;
}

void		process_command()
{
  t_list_head	*team_pos;
  t_list_head	*team_next;
  t_list_head	*player_pos;
  t_list_head	*player_next;
  t_team	*team;

  team_pos = list_get_first(&game.teams);
  while (team_pos != &game.teams)
    {
      team_next = team_pos->next;
      team = list_entry(team_pos, t_team, list);
      player_pos = list_get_first(&team->players);
      while (player_pos != &team->players)
	{
	  player_next = player_pos->next;
	  process_player(list_entry(player_pos, t_player, list));
	  player_pos = player_next;
	}
      team_pos = team_next;
    }
}
