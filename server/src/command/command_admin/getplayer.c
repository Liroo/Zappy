/*
** getplayer.c for Project-Master in /home/guicha/tek2/Zappy/server/src/command/command_admin
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Thu Jun 29 10:02:43 2017 guicha_t
** Last update Fri Jun 30 22:45:08 2017 guicha_t
*/

#include "debug.h"
#include "command.h"
#include "struct.h"
#include "h.h"

void	display_informations(t_client *client, t_player *player)
{
  /* queue_packet(client, SIMPLE_PACKET, "%d / %d\n", player->pos_x, player->pos_y); */
  (void)player;
  (void)client;
  /* queue_packet(client, SIMPLE_PACKET, RPL_OK); */
}

void	find_player_in_team(t_client *client, t_team *team)
{
  t_list_head	*head_p;
  t_list_head	*pos_p;
  t_client	*tmp_p;
  t_player	*player;

  head_p = &team->players;
  pos_p = list_get_first(head_p);
  while (pos_p != head_p)
    {
      tmp_p = list_entry(pos_p, t_client, list);
      player = tmp_p->data;
      display_informations(client, player);
      pos_p = pos_p->next;
    }
  (void)client;
  (void)team;
}

int	cmd_getplayer(t_client *client, char *token)
{
  t_list_head	*head;
  t_list_head	*pos;
  t_team	*team;
  /* t_player	*admin; */


  queue_packet(client, SIMPLE_PACKET, "In cmd getplayer\n");
  PRINT_DEBUG("In CMD getplayer\n");
  /* admin = client->data; */
  queue_packet(client, SIMPLE_PACKET, RPL_OK);
  (void)token;
  head = &game.teams;
  pos = list_get_first(head);
  while (pos != head)
    {
      team = list_entry(pos, t_team, list);
      find_player_in_team(client, team);
      pos = pos->next;
    }
  /* admin->command_is_running = 1; */
  /* queue_chrono(CHRONO_FORWARD, client, C_EVENT_COMMAND); */
  return (0);
}
