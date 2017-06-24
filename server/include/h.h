/*
** h.h for h in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 00:59:56 2017 Pierre Monge
** Last update Fri Jun 23 22:20:21 2017 Thomas
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
** dispatch fdevent using select
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
extern void	clear_packet(t_packet *packet);

/*
** Command
*/
extern void	convert_packet_to_command(t_packet packet,
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
extern int	cmd_set(t_player *p, char *token);
extern char	*parse_param(char *token);
extern char	*strepur(char *str);
extern int	cmd_look(t_player *p, char *token);
extern void	print_tiles(t_player *p, int x, int y);
extern void	send_vertical_look(t_player *p, int range, int begin_direction, int dir_y);
extern void	send_horizontal_look(t_player *p, int range, int begin_direction, int dir_x);
extern int	cmd_eject(t_player *p, char *token);
extern int	cmd_broadcast(t_player *p, char *token);
extern int	algorithme_vector(t_player *p_send, t_player *p_dest);
extern int	get_config_vector(int x, int y, int xmax, int ymax);
extern int	get_dir_config_one(int x, int y);
extern int	get_dir_config_two(int x, int ymax, int send_y, int dest_y);
extern int	get_dir_config_three(int xmax, int y, int sendx, int destx);
extern int	get_dir_config_four(int x, int y, t_player *s, t_player *d);
extern int	get_diff_max_y(t_player *send, t_player *dest);
extern int	get_diff_max_x(t_player *send, t_player *dest);

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
extern void	init_opt(t_game *game);
extern int	c_opt(t_game *game, int ac, char *av[]);
extern int	f_opt(t_game *game, int ac, char *av[]);
extern int	n_opt(t_game *game, int ac, char *av[]);
extern int	p_opt(t_game *game, int ac, char *av[]);
extern int	x_opt(t_game *game, int ac, char *av[]);
extern int	y_opt(t_game *game, int ac, char *av[]);

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
extern void		queue_chrono(int duration_s,
				     void *data,
				     char event_type);
extern void		insert_chrono_queue(t_chrono_queue *chrono);
extern void		create_chrono(t_chrono_queue *chrono,
				      int duration_s,
				      void *data, char
				      event_type);

extern int			compare_time(struct timespec ts1,
					     struct timespec ts2);
extern struct timespec		add_time(struct timespec ts1,
					 struct timespec ts2);
extern struct timespec		sub_time(struct timespec ts1,
					 struct timespec ts2);
extern void			delete_chrono_player(t_player *player);
extern void			delete_chrono(t_chrono_queue *chrono);
extern t_chrono_event_func	*get_chrono_event_func_list();

/*
** Process
*/
extern void	process_chrono_event();
extern void	process_command();

/*
** Event
*/
extern void	event_command(void *data);
extern void	event_lifetime(void *data);
extern void	event_timeout(void *data);

#endif /* !H_H */
