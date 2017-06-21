/*
** cmd_take.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Wed Jun 21 02:09:58 2017 guicha_t
** Last update Wed Jun 21 05:08:07 2017 guicha_t
*/

#include <string.h>

#include "debug.h"
#include "h.h"
#include "struct.h"

void	extract_linemate(t_player *p)
{
  if (game.map[p->pos_x][p->pos_y].linemate == 0)
    queue_packet(p, "ko\n");
  else
    {
      --game.map[p->pos_x][p->pos_y].linemate;
      ++p->inventory.linemate;
      queue_packet(p, "ok\n");
    }
}

void	extract_deraumere(t_player *p)
{
  if (game.map[p->pos_x][p->pos_y].deraumere == 0)
    queue_packet(p, "ko\n");
  else
    {
      --game.map[p->pos_x][p->pos_y].deraumere;
      ++p->inventory.deraumere;
      queue_packet(p, "ok\n");
    }
}

int	cmd_take(t_player *p, char *token)
{
  char		*rsc;
  unsigned int	i;

  // A refaire en + opti et voire compilable. 
  i = 0;
  while (token[i] != ' ' && token[i] != '\0')
    i++;
  if (i == strlen(token))
    return (1); // No param with 'take' cmd.
  rsc = &token[i];
  //
  if (strcmp(rsc, "linemate") == 0)
    extract_linemate(p);
  else if (strcmp(rsc, "deraumere") == 0)
    extract_deraumere(p);
  else if (strcmp(rsc, "sibur") == 0)
    extract_sibur(p);
  else if (strcmp(rsc, "mendiane") == 0)
    extract_mendiane(p);
  else if (strcmp(rsc, "phiras") == 0)
    extract_phiras(p);
  else if (strcmp(rsc, "thystame") == 0)
    extract_thystame(p);
  else if (strcmp(rsc, "food") == 0)
    extract_food(p);
  else
    queue_packet(p, "ko\n");
  //implémentation d'un tab de ptr de fctn.
  return (0);
}
