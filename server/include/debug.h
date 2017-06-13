/*
** debug.h for debug in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 13 10:38:17 2017 Pierre Monge
** Last update Tue Jun 13 12:15:06 2017 Pierre Monge
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

/*
** debug_array - debug function to print string array
**
** fname: completed by the macro PRINT_DEBUG_ARRAY, this is the first thing
** the function will print
** sarray: array of char* to print
** len: len of sarray
*/
void	debug_array(const char *fname, char * const *sarray, size_t len);
# define PRINT_DEBUG_ARRAY(sarray, len) debug_array(__PRETTY_FUNCTION__, \
						    sarray, len)

#endif /* !DEBUG_H */
