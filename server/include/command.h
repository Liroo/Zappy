/*
** command.h for Project-Master in /home/guicha/tek2/PSU_2016_zappy/server/include
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Thu Jun 15 23:05:33 2017 guicha_t
** Last update Fri Jun 16 00:28:58 2017 guicha_t
*/

#ifndef _COMMAND_H
# define _COMMAND_H

# define MAX_COMMAND_SIZE	1

typedef int	(*t_command_func)();

typedef struct		s_command
{
  char			*title;
  t_command_func	exe;
  
}			t_command;

typedef struct	s_token
{
  char		*token;
  int		is_over;
  
}		t_token;


#endif /* _COMMAND_H */
