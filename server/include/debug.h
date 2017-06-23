/*
** debug.h for debug in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 13 10:38:17 2017 Pierre Monge
** Last update Sat Jun 24 01:49:14 2017 Pierre Monge
*/

#ifndef DEBUG_H
# define DEBUG_H

# include <stdarg.h>
# include <stddef.h>

# define DEBUG_RED "\e[0;31m"
# define DEBUG_CLEAR "\e[0m"

/*
** debug - debug function to print basic things
** (like fprintf strerr but with function name)
**
** format: format used as printf
** __VA_ARGS__: va_list containing multiple arguments to print
*/
void	debug(const char * restrict format, ...);
# define DEBUG_PREFIX_SIZE DEBUG_RED"%s:"DEBUG_CLEAR" "
# define PRINT_DEBUG(format, ...) debug(DEBUG_PREFIX_SIZE""format,	\
					__PRETTY_FUNCTION__,		\
					##__VA_ARGS__)

#endif /* !DEBUG_H */
