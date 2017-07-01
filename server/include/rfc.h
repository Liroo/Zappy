/*
** rfc.h for rfc in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 19:39:29 2017 Pierre Monge
** Last update Sat Jul  1 05:02:24 2017 guicha_t
*/

#ifndef RFC_H
# define RFC_H

# define RPL_RFC_01 "01 %d %d\n"
# define RPL_RFC_02 "02 %s"
# define RPL_RFC_02_FD " %d"
# define RPL_RFC_02_END "\n"
# define RPL_RFC_03 "03 %d %d %d %d %d "		\
  "[linemate %d, deraumere %d, sibur %d,"		\
  " mendiane %d, phiras %d, thystame %d, food %d]\n"
# define RPL_RFC_04 "04 %d %d "				\
  "[linemate %d, deraumere %d, sibur %d,"		\
  " mendiane %d, phiras %d, thystame %d, food %d]\n"
# define RPL_RFC_05 "05 %d %d %d\n"
# define RPL_RFC_06 "06 %d %d\n"
# define RPL_RFC_07 "07 %d %d\n"
# define RPL_RFC_08 "08 %d\n"
# define RPL_RFC_09 "09 %d\n"
# define RPL_RFC_10 "10 %d\n"
# define RPL_RFC_11 "11 %d\n"
# define RPL_RFC_12 "12 %d\n"
# define RPL_RFC_13 "13 %d %s\n"
# define RPL_RFC_14 "14 %d %s\n"

extern void	rfc(t_client *spectator, const char * restrict format, ...);
extern void	rfc_auth(t_client *spectator);

extern void	rfc_01(t_client *spectator);
extern void	rfc_02(t_client *spectator, t_team *team);
extern void	rfc_03(t_client *spectator, t_client *client);
extern void	rfc_04(t_client *spectator, int x, int y);
extern void	rfc_05(t_client *spectator, t_client *client);
extern void	rfc_06(t_client *spectator, t_client *client);
extern void	rfc_07(t_client *spectator, t_client *client);
extern void	rfc_08(t_client *spectator, t_client *client);
extern void	rfc_09(t_client *spectator, t_client *client);
extern void	rfc_10(t_client *spectator, t_client *client, char *text);
extern void	rfc_11(t_client *spectator, t_client *client);
extern void	rfc_12(t_client *spectator, t_client *client);
extern void	rfc_13(t_client *spectator, t_client *client, char *object);
extern void	rfc_14(t_client *spectator, t_client *client, char *object);

#endif /* !RFC_H */
