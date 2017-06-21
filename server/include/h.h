/*
** h.h for h in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 00:59:56 2017 Pierre Monge
** Last update Wed Jun 21 21:52:06 2017 guicha_t
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
extern int	fd_select(struct timespec *duration);

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
extern void	queue_packet(t_player *player, char dead_packet,
			     char *format, ...);
extern void	send_queued_packet(t_player *player);

/*
** Command
*/
extern void			convert_packet_to_command(t_packet packet,
						  t_player *player);

/*
** Unit cmds
*/
extern int	cmd_forward(t_player *p, char *token);
extern int	cmd_left(t_player *p, char *token);
extern int	cmd_right(t_player *p, char *token);
extern int	cmd_take(t_player *p, char *token);
extern int	cmd_connect_nbr(t_player *p, char *token);
extern int	cmd_inventory(t_player *p, char *token);

/*
** Extraction
*/
extern void	extract_sibur(t_player *p);
extern void	extract_mendiane(t_player *p);
extern void	extract_phiras(t_player *p);
extern void	extract_thystame(t_player *p);
extern void	extract_food(t_player *p);

/*
** Free class
*/
extern void	delete_player(t_player *player);
extern void	delete_teams();
extern void	delete_game();


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

/*
** Map
*/
extern void	insert_objects_in_map(int offset, int nb);
extern int	generate_map();

/*
** Chrono
*/
extern void	queue_chrono(int duration_s, void *data, char event_type);
extern void	insert_chrono_queue(t_chrono_queue *chrono);
extern void	create_chrono(t_chrono_queue *chrono, int duration_s,
			      void *data, char event_type);
extern int	diff_time(t_chrono_queue *c1, t_chrono_queue *c2);

/*
** Process
*/
extern void	process_chrono_event();

#endif /* !H_H */
