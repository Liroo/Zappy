//
// LTexture.hpp for ltexture in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
// 
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
// 
// Started on  Mon Jun 26 00:57:46 2017 Lucas
// Last update Sat Jul  1 20:45:38 2017 Lucas
//

#ifndef LTexture_HPP
# define LTexture_HPP

/*
** Personnal header inclusions.
*/
# include "zappy.hpp"

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
  irr::video::ITexture		*getTile() const;

private:
  // MAP OBJECTS //
  irr::video::ITexture		*tile;
  
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
