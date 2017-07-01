//
// zappy.hpp for zappy in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
// 
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
// 
// Started on  Sun Jun 25 22:00:45 2017 Lucas
// Last update Fri Jun 30 17:58:52 2017 Lucas
//

#ifndef ZAPPY_HPP_
# define ZAPPY_HPP_

/*
** Macro definitions.
*/
# define	GUI_OK		(0)
# define	GUI_ERR		(-1)
# define	FPS		(10)
# define	STATIC		(11)

/*
** Error macro definitions.
*/
# define        ENGINE_ERR      "Failed to initialize sound engine."

/*
** Log font macro definitions.
*/
# define RED		"\033[1;31m"
# define GREEN           "\033[1;32m"
# define BLUE            "\033[1;34m"
# define YELLOW          "\033[1;33m"
# define BLANK		"\033[0m"

/*
** Std & library headers inclusions.
*/
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

/*
** Structure type definitions.
*/
typedef struct                  s_sett
{
  bool                          on_off;
  irrklang::ISoundEngine        *engine;
  irrklang::ISound              *lobbySound;
}				t_sett;

/*
** Enum type definitions.
*/
enum	Anim
  {
    NO_ANIM = 0,
    MOVE = 1,
    VICTORY = 2,
    DEFEAT = 3
  };

enum    Win
  {
    LOBBY = 0,
    GUI = 1,
    SETTINGS = 2,
    CREDITS = 3,
    EOG = 4
  };
typedef Win WinType;

enum
  {
    GUI_ID_CONNECT_BUTTON = 101,
    GUI_ID_EXIT_BUTTON,
    GUI_ID_SETT_BUTTON,
    GUI_ID_CREDITS_BUTTON
  };

#endif /* !ZAPPY_HPP_ */
