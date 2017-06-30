/*
** admin.h for Project-Master in /home/guicha/tek2/Zappy/admin/include
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Thu Jun 29 09:46:29 2017 guicha_t
** Last update Thu Jun 29 10:00:18 2017 guicha_t
*/

#pragma once

class	ClientAdmin
{
 private:
  int	port;
  char	*name;
  char	*ip;
  
 public:
  ClientAdmin();
  ~ClientAdmin();
}
