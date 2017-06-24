/*
** cmd_broadcast.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Thu Jun 22 07:01:19 2017 guicha_t
** Last update Fri Jun 23 16:38:49 2017 guicha_t
*/

#include "debug.h"
#include "game.h"
#include "chrono.h"
#include "struct.h"
#include "h.h"
#include "packet.h"

void	find_player_broadcast(t_player *send, t_team *team, char *t)
{
  t_list_head	*head_p;
  t_list_head	*pos_p;
  t_player	*tmp_p;
  int		dir;

  head_p = &team->players;
  pos_p = list_get_first(head_p);
  while (pos_p != head_p)
    {
      tmp_p = list_entry(pos_p, t_player, list);
      dir = algorithme_vector(send, tmp_p);
      (void)dir;
      (void)t;
      PRINT_DEBUG("message %d, %s\n", dir, t);
      // ecrire dans player avec la dir en fonction
      // de la dir player + le texte.
      pos_p = pos_p->next;
    }
}

int	cmd_broadcast(t_player *p, char *token)
{
  t_list_head	*head;
  t_list_head	*pos;
  t_team	*team;

  head = &game.teams;
  pos = list_get_first(head);
  while (pos != head)
    {
      team = list_entry(pos, t_team, list);
      find_player_broadcast(p, team, token);
      pos = pos->next;
    }
  queue_packet(p, SIMPLE_PACKET, RPL_OK);
  p->command_is_running = 1;
  queue_chrono(CHRONO_BROADCAST, p, C_EVENT_COMMAND);
  return (0);
}
