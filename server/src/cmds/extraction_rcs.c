/*
** extraction_rcs.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Wed Jun 21 04:56:10 2017 guicha_t
** Last update Wed Jun 21 05:07:31 2017 guicha_t
*/

#include "h.h"
#include "debug.h"
#include "struct.h"

void	extract_sibur(t_player *p)
{
  if (game.map[p->pos_x][p->pos_y].sibur == 0)
    queue_packet(p, "ko\n");
  else
    {
      --game.map[p->pos_x][p->pos_y].sibur;
      ++p->inventory.sibur;
      queue_packet(p, "ok\n");
    }
}

void	extract_mendiane(t_player *p)
{
  if (game.map[p->pos_x][p->pos_y].mendiane == 0)
    queue_packet(p, "ko\n");
  else
    {
      --game.map[p->pos_x][p->pos_y].mendiane;
      ++p->inventory.mendiane;
      queue_packet(p, "ok\n");
    }
}

void	extract_phiras(t_player *p)
{
  if (game.map[p->pos_x][p->pos_y].phiras == 0)
    queue_packet(p, "ko\n");
  else
    {
      --game.map[p->pos_x][p->pos_y].phiras;
      ++p->inventory.phiras;
      queue_packet(p, "ok\n");
    }
}

void	extract_thystame(t_player *p)
{
  if (game.map[p->pos_x][p->pos_y].thystame == 0)
    queue_packet(p, "ko\n");
  else
    {
      --game.map[p->pos_x][p->pos_y].thystame;
      ++p->inventory.thystame;
      queue_packet(p, "ok\n");
    }
}

void	extract_food(t_player *p)
{
  if (game.map[p->pos_x][p->pos_y].food == 0)
    queue_packet(p, "ko\n");
  else
    {
      --game.map[p->pos_x][p->pos_y].food;
      ++p->inventory.food;
      queue_packet(p, "ok\n");
    }
}


