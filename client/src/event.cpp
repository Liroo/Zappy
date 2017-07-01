//
// event.cpp for updatewin in /home/lucas/Zappy/client/src
// 
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
// 
// Started on  Thu Jun 29 16:34:55 2017 Lucas
// Last update Sat Jul  1 04:00:10 2017 Lucas
//

#include "eventGesture.hpp"

bool		Event::OnEvent(const irr::SEvent &event)
{
  irr::s32	status;

  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
      switch (event.KeyInput.Key)
	{
	case (irr::KEY_ESCAPE):
	  std::cout << "EVENT ESCAPE" << std::endl;
	  quit = true;
	  break;
	case (irr::KEY_KEY_7):
	  std::cout << "CATCH" << std::endl;
	  break;
	default:
	  break;
	}
    }
  if (event.EventType == irr::EET_GUI_EVENT &&
      win != EOG)
    {
      status = event.GUIEvent.Caller->getID();
      switch (event.GUIEvent.EventType)
	{
	case irr::gui::EGET_BUTTON_CLICKED:
	  switch (status)
	    {
	    case GUI_ID_CONNECT_BUTTON:
	      pressConnect = true;
	      return (false);
	    default:
	      return (false);
	    }
	default:
	  return (false);
	}
    }
  return (false);
}

void	Event::setPressConnect(bool update)
{
  this->pressConnect = update;
}

bool	Event::getPressConnect() const
{
  return (this->pressConnect);
}

bool	Event::getQuit() const
{
  return (this->quit);
}

Event::Event()
{
  quit = false;
  goBackLobby = false;
  goBackspace = false;
  goReturn = false;
  didClick = false;
  onEvent = 0;
  win = LOBBY;
  pressConnect = false;
}

Event::~Event()
{}
