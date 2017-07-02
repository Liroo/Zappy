//
// LTexture.hpp for ltexture in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
//
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
//
// Started on  Mon Jun 26 00:57:46 2017 Lucas
// Last update Sun Jul  2 16:48:18 2017 Lucas
//

#ifndef LTexture_HPP
# define LTexture_HPP

/*
** Standard header inclusions.
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
# include <map>
# include <iostream>

/*
** Macro definitions.
*/
# define	GUI_OK	(0)
# define	GUI_ERR	(-1)

/*
** Class that will be used to handle the texture loading process.
*/
class LTexture
{
public:
  LTexture();
  ~LTexture();
  int				initDevice();
  int				setTexture(irr::scene::ISceneManager *, irr::video::IVideoDriver *,
					   irr::gui::IGUIEnvironment *);
  // LOBBY //
  irr::video::ITexture		*getLogo() const;
  irr::video::ITexture		*getHostL() const;
  irr::video::ITexture		*getPortL() const;
  irr::video::ITexture		*getConnectL() const;

  // SKYBOX //
  irr::video::ITexture*		getSbMountUp() const;
  irr::video::ITexture*         getSbMountDown() const;
  irr::video::ITexture*         getSbMountRight() const;
  irr::video::ITexture*         getSbMountLeft() const;
  irr::video::ITexture*         getSbMountFront() const;
  irr::video::ITexture*         getSbMountBack() const;

  // MAP OBJECTS //
  irr::video::ITexture		*getGroundPng() const;
  irr::scene::IAnimatedMesh     *getBricksObj() const;
  irr::video::ITexture		*getPlayerPng() const;


private:
  // MAP OBJECTS //
  irr::video::ITexture*                     BRICKS_MENU_PNG;
  irr::scene::IAnimatedMesh*                BRICKS_MENU_OBJ;
  irr::video::ITexture*                     GROUND_PNG;
  irr::video::ITexture*			    PLAYER_PNG;

  // LOBBY //
  irr::video::ITexture		*LogoPNG;
  irr::video::ITexture		*hostLogo;
  irr::video::ITexture		*portLogo;
  irr::video::ITexture		*connectLogo;

  // SKYBOX //
  irr::video::ITexture	       *SKYBOX_MOUNT_UP;
  irr::video::ITexture         *SKYBOX_MOUNT_DOWN;
  irr::video::ITexture         *SKYBOX_MOUNT_LEFT;
  irr::video::ITexture         *SKYBOX_MOUNT_RIGHT;
  irr::video::ITexture         *SKYBOX_MOUNT_FRONT;
  irr::video::ITexture         *SKYBOX_MOUNT_BACK;

};

#endif	/* !LTexture_HPP */
