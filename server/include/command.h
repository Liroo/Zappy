/*
** command.h for Project-Master in /home/guicha/tek2/PSU_2016_zappy/server/include
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Thu Jun 15 23:05:33 2017 guicha_t
** Last update Thu Jun 29 12:57:27 2017 guicha_t
*/

#ifndef _COMMAND_H
# define _COMMAND_H

# define MAX_COMMAND_SIZE_PLAYER 12
# define MAX_COMMAND_SIZE_ADMIN 1

typedef struct s_command	t_command;
typedef struct s_command_queue	t_command_queue;
typedef struct s_client		t_client;

typedef int	(*t_command_func)(t_client *client, char *command);

struct			s_command
{
  char			*title;
  int			title_len;
  t_command_func	exec;
};

struct			s_command_queue
{
  char			*command;
  t_command_func	exec;
};

#endif /* _COMMAND_H */
