/*
** h.h for h in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 00:59:56 2017 Pierre Monge
** Last update Thu Jun 15 06:04:43 2017 Pierre Monge
*/

#ifndef H_H
# define H_H

# include <time.h>

# define MAX_CONNECTIONS 10240

/*
** bsd func
*/
extern int	inetport(int port);
extern void	accept_connection(int sock_fd);
extern void	add_connection(int fd);

/*
** socket
*/
extern int	zappy_bind(int fd, int port);
extern int	socket_setopt(int fd, int socket_opt);
extern int	zappy_socket();
extern int	socket_close(int fd);

/*
** fdlist
*/
extern int	fd_open(int fd);
extern int	fd_unmap(int fd);
extern int	fd_close(int fd);
extern int	fd_accept(int sockfd);

/*
** dispatch event using select
*/
extern void	fd_set_select(int fd, int flag, void *data);
extern void	fd_refresh(int fd);
extern int	fd_select(time_t delay);

/*
** signal
*/
extern int	sig_set(char to_handle);
extern void	sig_handler(int sig);



#endif /* !H_H */
