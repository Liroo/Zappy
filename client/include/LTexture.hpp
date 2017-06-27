//
// LTexture.hpp for ltexture in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
// 
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
// 
// Started on  Mon Jun 26 00:57:46 2017 Lucas
// Last update Mon Jun 26 23:48:57 2017 Lucas
//

#ifndef LTexture_HPP
# define LTexture_HPP

/*
** Personnal header inclusions.
*/
# include "zappy.hpp"

class LTexture
{
public:
  LTexture();
  ~LTexture();
  int				initDevice();
  int				setTexture(irr::scene::ISceneManager *, irr::video::IVideoDriver *,
					   irr::gui::IGUIEnvironment *);
  irr::video::ITexture		*getLogo() const;
  irr::scene::IAnimatedMesh	*getLogoOBJ() const;

  irr::video::ITexture*		getSbMountUp() const;
  irr::video::ITexture*         getSbMountDown() const;
  irr::video::ITexture*         getSbMountRight() const;
  irr::video::ITexture*         getSbMountLeft() const;
  irr::video::ITexture*         getSbMountFront() const;
  irr::video::ITexture*         getSbMountBack() const;
  

private:
  irr::video::ITexture		*LogoPNG;
  irr::scene::IAnimatedMesh	*LogoOBJ;

  // SKYBOX //
  irr::video::ITexture	       *SKYBOX_MOUNT_UP;
  irr::video::ITexture         *SKYBOX_MOUNT_DOWN;
  irr::video::ITexture         *SKYBOX_MOUNT_LEFT;
  irr::video::ITexture         *SKYBOX_MOUNT_RIGHT;
  irr::video::ITexture         *SKYBOX_MOUNT_FRONT;
  irr::video::ITexture         *SKYBOX_MOUNT_BACK;
  
};

#endif	/* !LTexture_HPP */
