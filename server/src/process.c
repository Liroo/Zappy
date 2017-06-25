/*
** process.c for process in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Wed Jun 21 04:30:29 2017 Pierre Monge
** Last update Sun Jun 25 02:17:37 2017 Pierre Monge
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

static void	process_player(t_client *client)
{
   int		i;
   t_player	*player;

   player = client->data;
   if (player->command_is_running || player->command_in_queue <= 0)
     return ;
   if ((*player->command_queue).exec)
     (*player->command_queue).exec(client, (*player->command_queue).command);
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

static void	process_admin(t_client *client)
{
   int		i;
   t_admin	*admin;

   admin = client->data;
   if ((*admin->command_queue).exec)
     (*admin->command_queue).exec(client, (*admin->command_queue).command);
   free((*admin->command_queue).command);
   (*admin->command_queue).command = NULL;
   i = 0;
   while (i < admin->command_in_queue)
     {
       admin->command_queue[i] = admin->command_queue[i + 1];
       i++;
     }
   admin->command_in_queue -= 1;
}

static void	process_client_list(t_list_head *head)
{
  t_list_head	*pos;
  t_list_head	*next;
  t_client	*client;

  pos = list_get_first(head);
  while (pos != head)
    {
      next = pos->next;
      client = list_entry(pos, t_client, list);
      if (client->client_type == ADMIN)
	process_admin(client);
      else if (client->client_type == PLAYER)
	process_player(client);
      pos = next;
    }
}

void		process_command()
{
  t_list_head	*team_pos;
  t_list_head	*team_next;
  t_team	*team;

  process_client_list(&game.admins);
  team_pos = list_get_first(&game.teams);
  while (team_pos != &game.teams)
    {
      team_next = team_pos->next;
      team = list_entry(team_pos, t_team, list);
      process_client_list(&team->players);
      team_pos = team_next;
    }
}
