//
// splash_screen.hpp for ss in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
// 
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
// 
// Started on  Mon Jun 26 00:47:57 2017 Lucas
// Last update Tue Jun 27 01:04:12 2017 Lucas
//

#ifndef SPLASH_SCREEN_HPP_
# define SPLASH_SCREEN_HPP_

/*
** Personnal header inclusions.
*/
# include "LTexture.hpp"

/*
** Macro definitions.
*/
# define	TIMER	(5)
# define	LOGO_PATH	"./media/img/zappyLogo.png"

/*
** Splash Screen class, used while loading the GUI.
*/
class Ss : public LTexture
{
public:
  Ss(irr::scene::ISceneManager *, irr::video::IVideoDriver *, irr::IrrlichtDevice *);
  ~Ss();
  int           splashScreen();
private:
  irr::scene::ISceneManager		*sm;
  irr::video::IVideoDriver		*driver;
  irr::IrrlichtDevice			*device;

  void  makeCamera(int type);
  void  makeBodies(int x, int y, int z,
		       int rx, int ry, int rz,
		       int ex, int ey, int ez);
  void  makeSkybox();
  void  ss_remove();
  void  makeLogo();

  irr::SKeyMap                       keyMap[6];

  std::chrono::time_point<std::chrono::system_clock>
  start;

  irr::scene::IAnimatedMeshSceneNode*	ssBodies;
  irr::scene::IAnimatedMeshSceneNode*	ssLogo;

  irr::scene::ISceneNode*		skybox;

  irr::scene::ICameraSceneNode*         ssCamera;
  bool				       	quit;

  irr::gui::IGUIEnvironment*            ssGUI;
  irr::video::ITexture*			zappyLogo;
};


#endif	/* !SPLASH_SCREEN_HPP_ */
