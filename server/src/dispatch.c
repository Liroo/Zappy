/*
** dispatch.c for dispatch in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 04:14:35 2017 Pierre Monge
** Last update Fri Jun 16 01:26:55 2017 guicha_t
*/

#include <sys/select.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>

#include "h.h"
#include "fdlist.h"
#include "event.h"
#include "debug.h"
#include "struct.h"

void		fd_set_select(int fd, int flags, void *data)
{
  t_fd_entry	*fde;

  if ((fd < 0) || (fd >= MAX_CONNECTIONS))
    return ;
  fde = &fd_entry[fd];
  fde->data = data;
  fde->flags = flags;
  fd_refresh(fd);
}

t_fdset	fdset;

void	fd_refresh(int fd)
{
  t_fd_entry	*fde;

  fde = &fd_entry[fd];
  if (fde->flags & FD_SELECT_READ)
    FD_SET(fd, &fdset.read_fds);
  else
    FD_CLR(fd, &fdset.read_fds);
  if (fde->flags & FD_SELECT_WRITE)
    FD_SET(fd, &fdset.write_fds);
  else
    FD_CLR(fd, &fdset.write_fds);
  if (fde->flags && fdset.highest_fd < fd)
    fdset.highest_fd = fd;
  while (fdset.highest_fd > 0 &&
	 !(FD_ISSET(fdset.highest_fd, &fdset.read_fds) ||
	   FD_ISSET(fdset.highest_fd, &fdset.write_fds)))
    fdset.highest_fd--;
}

static EVENT	get_event_flags(int fd, fd_set read_fds, fd_set write_fds)
{
  EVENT		event_flags;

  event_flags = 0;
  if (FD_ISSET(fd, &read_fds))
    event_flags |= FD_SELECT_READ;
  if (FD_ISSET(fd, &write_fds))
    event_flags |= FD_SELECT_WRITE;
  return (event_flags);
}

static int	fd_dispatch(int num, fd_set read_fds, fd_set write_fds)
{
  t_fd_entry	*fde;
  int		fd;
  EVENT		event_flags;

  PRINT_DEBUG("dispatching %d events...\n", num);
  fd = 0;
  while (fd <= fdset.highest_fd && num > 0)
    {
      fde = &fd_entry[fd];
      if ((!fde->is_open) ||
	  !(event_flags = get_event_flags(fd, read_fds, write_fds)))
	{
	  fd++;
	  continue;
	}
      if (event_flags | FD_SELECT_READ)
	read_on_fd(fde->data); // Here we have to read on fd */
      if (event_flags | FD_SELECT_WRITE)
	(void)1; // Here we have to write on fd
      fd++;
      num--;
    }
  return (0);
}

int			fd_select(time_t delay)
{
  struct timespec	to;
  int			num;
  fd_set		cpy_read_fds;
  fd_set		cpy_write_fds;
  sigset_t		emptyset;

  memcpy(&cpy_read_fds, &fdset.read_fds, sizeof(fd_set));
  memcpy(&cpy_write_fds, &fdset.write_fds, sizeof(fd_set));
  memset(&to, 0, sizeof(struct timeval));
  to.tv_sec = delay / 1000;
  to.tv_nsec = (delay % 1000) * 1000 * 1000;
  sigemptyset(&emptyset);
  num = pselect(fdset.highest_fd + 1,
    &cpy_read_fds, &cpy_write_fds, NULL, &to,
    &emptyset);
  if (num < 0)
    return (perror("select"), -1);
  if (num == 0)
    return (0);
  if (FD_ISSET(game.net_info.fd, &cpy_read_fds))
    {
      accept_connection(game.net_info.fd);
      num--;
    }
  return (fd_dispatch(num, cpy_read_fds, cpy_write_fds));
}
