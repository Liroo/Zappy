/*
** ConnectClient.h for zappy in /home/thomas/Rendu/Zappy/client/include
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Wed Jun 28 00:50:35 2017 Thomas
// Last update Sun Jul  2 18:36:19 2017 Lucas
*/

#ifndef CONNECTCLIENT_H
# define CONNECTCLIENT_H

# include <irrlicht.h>
# include <iostream>
# include <fstream>
# include <chrono>
# include <ctime>
# include <vector>
# include <thread>
# include <string>
# include <mutex>
# include <limits>
# include <time.h>
# include <irrKlang.h>
# include <sstream>
# include <sys/types.h>
# include <unistd.h>

# include "gnl.hpp"

# define	PARAM_OK	(2)

class ConnectClient {

public:
  ConnectClient(int, std::string, bool param, irr::scene::ISceneManager*,
		irr::video::IVideoDriver*, irr::IrrlichtDevice*);
  ~ConnectClient();

private:
  irr::video::IVideoDriver      *driver;
  irr::scene::ISceneManager     *smgr;
  irr::IrrlichtDevice           *device;
  irr::gui::IGUIEnvironment     *coGUI;

  int			_port;
  int			_save_port;
  std::string		_host;
  std::string		_save_host;
  int			_fd;
  fd_set		_fd_read;
  struct timeval	_tv;
  bool			_checkParam;
  std::string		_buf;
  Gnl			*_gnl;

private:
  int	clienttoserv();
  int	servtoclient();
  int	add_server_to_client();
  int	firstConnect();

public:
  int		myConnect();
  int		my_select();
  std::string	getResponse() const;
  void		clearResponse();

};

#endif
