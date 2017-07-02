/*
** command.h for Project-Master in /home/guicha/tek2/PSU_2016_zappy/server/include
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Thu Jun 15 23:05:33 2017 guicha_t
** Last update Sun Jul  2 22:23:16 2017 Pierre Monge
*/

#ifndef COMMAND_H
# define COMMAND_H

# define MAX_COMMAND_SIZE_PLAYER 12
# define MAX_COMMAND_SIZE_ADMIN 6
# define GET_INVENTORY "FD\t\t%d\nFood:\t\t%d\nLinemate:\t%d\n" \
  "Deraumere:\t%d\nSibur:\t\t%d\n" \
  "Mendiane:\t%d\nPhiras:\t\t%d\nThystame:\t%d\n"

typedef struct s_command	t_command;
typedef struct s_command_queue	t_command_queue;
typedef struct s_client		t_client;

typedef int	(*t_command_func)(t_client *client, char *command);

struct			s_command
{
  char			*title;
  int			title_len;
  int			duration;
  t_command_func	exec;
  t_command_func	pre_exec;
};

struct			s_command_queue
{
  char			*command;
  int			duration;
  t_command_func	exec;
  t_command_func	pre_exec;
};

#endif /* !COMMAND_H */
