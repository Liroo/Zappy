//
// initGui.cpp for initgui in /home/lucas/Zappy/server
//
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
//
// Started on  Sun Jul  2 05:30:31 2017 Lucas
// Last update Sun Jul  2 22:04:56 2017 Thomas
//

#include "game.hpp"

void		Game::makeGround(int x, int y)
{
  if (getMapX() >= 20 || getMapY() >= 20)
    {
      gameBrick[nbGround] = _sm->addAnimatedMeshSceneNode(getBricksObj(),
							 0, -1,
							 irr::core::vector3df(x+600, y+1000, -1740.0f),
							 irr::core::vector3df(0.0f, 0.0f, 0.0f),
							 irr::core::vector3df(4.0f, 4.0f, 4.0f));
    }
  else
    {
      gameBrick[nbGround] = _sm->addAnimatedMeshSceneNode(getBricksObj(),
							 0, -1,
							 irr::core::vector3df(x-400, y, -1740.0f),
							 irr::core::vector3df(0.0f, 0.0f, 0.0f),
							 irr::core::vector3df(4.0f, 4.0f, 4.0f));

    }
      gameBrick[nbGround]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      gameBrick[nbGround]->setMaterialTexture(0, getGroundPng());
  nbGround++;

}

void		Game::makeMap()
{
  int   y = 1300;
  int   x;
  int   a = 0;
  int   b = 0;

  nbGround = 0;
  while (a <= _map_x)
    {
      std::vector< t_tiles > sub;
      x = 1150;
      b = 0;
      while (b <= _map_y)
	{
	  t_tiles    tmp;
	  tmp.x = x;
	  tmp.y = y + 40;
	  tmp.available = true;
	  makeGround(x, y);
	  sub.push_back(tmp);
	  b++;
	  x -= 127;
	}
      a++;
      _map.push_back(sub);
      y -= 127;
    }
}
