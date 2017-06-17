/*
** command.h for Project-Master in /home/guicha/tek2/PSU_2016_zappy/server/include
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Thu Jun 15 23:05:33 2017 guicha_t
** Last update Sat Jun 17 05:22:00 2017 Pierre Monge
*/

#ifndef _COMMAND_H
# define _COMMAND_H

# define MAX_COMMAND_SIZE	12

typedef int	(*t_command_func)(t_player *player, char *command);

typedef struct		s_command
{
  char			*title;
  int			title_len;
  t_command_func	exec;
}			t_command;

typedef struct		s_command_queue
{
  char			*command;
  t_command_func	exec;
}			t_command_queue;

#endif /* _COMMAND_H */
