/*
** h.h for h in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 00:59:56 2017 Pierre Monge
** Last update Tue Jun 20 02:25:33 2017 Pierre Monge
*/

#ifndef H_H
# define H_H

# include <time.h>

#include "struct.h"
#include "event.h"

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

extern EVENT	get_event_flags(int fd, fd_set read_fds, fd_set write_fds);
extern void	read_event(t_player *player);
extern void	write_event(t_player *player);

/*
** signal
*/
extern int	sig_set(char to_handle);
extern void	sig_handler(int sig);

/*
** packet
*/
extern int	recv_packet(t_player *player);
extern void	queue_packet(t_player *player, char *format, ...);
extern void	send_queued_packet(t_player *player);

/*
** Command
*/
extern void			convert_packet_to_command(t_packet packet,
						  t_player *player);

/*
** Free class
*/
extern void	delete_player(t_player *player);
extern void	delete_teams();


/*
** Option
*/
extern t_game	*parse_option(int ac, char *av[], t_game *game);
extern void	c_opt(t_game *game, int ac, char *av[]);
extern void	f_opt(t_game *game, int ac, char *av[]);
extern void	n_opt(t_game *game, int ac, char *av[]);
extern void	p_opt(t_game *game, int ac, char *av[]);
extern void	x_opt(t_game *game, int ac, char *av[]);
extern void	y_opt(t_game *game, int ac, char *av[]);

/*
** Auth
*/
extern void	auth_player(t_packet packet, t_player *player);

#endif /* !H_H */
