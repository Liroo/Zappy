//
// eventGesture.hpp for eventGesture in /home/lucas/Zappy/client
// 
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
// 
// Started on  Thu Jun 29 16:00:47 2017 Lucas
// Last update Sat Jul  1 03:59:26 2017 Lucas
//

#ifndef EVENTGESTURE_HPP_
# define EVENTGESTURE_HPP_

/*
** Personnal header inclusions.
*/
# include "zappy.hpp"

/*
** This class will handle the event catching process.
*/
class Event : public irr::IEventReceiver
{
public:
  Event();
  ~Event();

  bool		getQuit() const;
  bool		getPressConnect() const;
  void		setPressConnect(bool);
  
  virtual bool	OnEvent(const irr::SEvent &event);


  void		doEscape();

  int		updateView(WinType dest);
private:
  bool		quit;
  bool		didClick;
  int		onEvent;

  bool		pressConnect;
  bool		goBackLobby;
  bool          goBackspace;
  bool          goReturn;
  Win		win;
};

#endif	/* !EVENTGESTURE_HPP_ */
