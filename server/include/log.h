/*
** log.h for log in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 23 23:03:54 2017 Pierre Monge
** Last update Sat Jun 24 01:17:16 2017 Pierre Monge
*/

#ifndef LOG_H
# define LOG_H

# define LOG_GREEN "\e[0;32m"
# define LOG_CLEAR "\e[0m"

void	print_log(const char * restrict format, ...);
# define PRINT_LOG(format, ...) print_log(format, ##__VA_ARGS__)

#endif /* !LOG_H */
