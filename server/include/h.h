/*
** h.h for h in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 00:59:56 2017 Pierre Monge
** Last update Sun Jul  2 21:55:57 2017 guicha_t
*/

#ifndef H_H
# define H_H

# include <stdarg.h>
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
** auth
*/
extern void	init_disable_log(t_client *client);

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
extern void	read_event(t_client *client);
extern void	write_event(t_client *client);

/*
** Pipe
*/
extern int	broken_pipe_empty_event(t_client *client);
extern void	broken_pipe(t_client *client);

/*
** signal
*/
extern int	sig_set(char to_handle);
extern void	sig_handler(int sig);

/*
** packet
*/
extern int	recv_packet(t_client *client);
extern void	queue_packet(t_client *client, char dead_packet,
			     char *format, ...);
extern void	queue_packet_va(t_client *client, char dead_packet,
			     char *format, va_list va);
extern int	send_queued_packet(t_client *client);
extern void	clear_packet(t_packet *packet);

/*
** Command
*/
extern void		queue_command_player(t_packet packet, t_client *client);
extern void		queue_command_spectator(t_packet packet, t_client *client);
extern void		queue_command_admin(t_packet packet, t_client *client);
extern t_command	*get_command_list_player();
extern t_command	*get_command_list_admin();

/*
** Unit cmds
*/
extern int	cmd_forward(t_client *client, char *token);
extern int	cmd_left(t_client *client, char *token);
extern int	cmd_right(t_client *client, char *token);
extern int	cmd_take(t_client *client, char *token);
extern int	cmd_connect_nbr(t_client *client, char *token);
extern int	cmd_inventory(t_client *client, char *token);
extern int	cmd_set(t_client *client, char *token);
extern int	cmd_look(t_client *client, char *token);
extern int	cmd_eject(t_client *client, char *token);
extern int	cmd_broadcast(t_client *client, char *token);
extern int	cmd_fork(t_client *client, char *token);
extern int	cmd_pre_elevation(t_client *client, char *token);
extern int	cmd_elevation(t_client *client, char *token);

extern void	elevate_players(int x, int y);
extern int	check_winning_condition();
extern char	*parse_param(char *token);
extern char	*strepur(char *str);
extern void	print_tiles(t_client *client, int x, int y);
extern int	algorithme_vector(t_player *p_send, t_player *p_dest);
extern int	get_config_vector(int x, int y, int xmax, int ymax);
extern int	get_dir_config_one(int x, int y);
extern int	get_dir_config_two(int x, int ymax, int send_y, int dest_y);
extern int	get_dir_config_three(int xmax, int y, int sendx, int destx);
extern int	get_dir_config_four(int x, int y, t_player *s, t_player *d);
extern int	get_diff_max_y(t_player *send, t_player *dest);
extern int	get_diff_max_x(t_player *send, t_player *dest);


/*
** Command Admin
*/
extern int	cmd_getplayer(t_client *client, char *token);
extern int	cmd_mvplayer(t_client *client, char *token);
extern int	my_count_word(char *str, char d);
extern int	cmd_disable_log(t_client *client, char *token);
extern int	cmd_able_log(t_client *client, char *token);
extern void	catch_each_param(char *token, char *src);
extern int	cmd_set_level(t_client *client, char *token);
extern int	cmd_get_inventory(t_client *client, char *token);
extern void	print_getinventory(t_client *client, t_client *player,
				   t_player *p);

/*
** Free class
*/
extern void	delete_game();
extern void	delete_egg(t_egg *egg);
extern void	delete_team(t_team *team);
extern void	delete_client(t_client *client);
extern void	delete_chronos();

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
extern void	auth_client(t_packet packet, t_client *client);

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
extern void			delete_chrono_client(t_client *client);
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
extern int	event_command(void *data);
extern int	event_lifetime(void *data);
extern int	event_timeout(void *data);
extern int	event_fork(void *data);

/*
** Exit
*/
extern int	zappy_exit();
extern void	end_server(t_team *team);
extern int	is_server_ended();

#endif /* !H_H */
