____________________________________________
Installation de Irrlicht sous Ubuntu/Debian:

-sudo apt-get install libirrlicht-dev	    
-sudo apt-get install libgl1-mesa-dev	    
-sudo apt-get install libxxf86vm-dev		    
-sudo apt-get install libxext-dev		    
-sudo apt-get install libxcursor-dev		    
-sudo cp irrklang/libIrrKlang.so /user/bin/

-----------------------------
 Install Irrlicht on mac osX:

- brew install irrlicht

______________________________________________________________
 Install de Irrlicht sous Opensuse (ou notre BLinux national):

-sudo apt-get install libXxf86vm-dev
-sudo apt-get install libXext-dev
-sudo apt-get install libXcursor-dev
-sudo zypper install Mesa-libGL-devel
-sudo zypper addrepo http://download.opensuse.org/repositories/games/openSUSE_Tumbleweed/games.repo
-sudo zypper refresh
-sudo zypper install irrlicht
-sudo cp irrklang/libIrrKlang.so /user/bin

______________________
 Lancement du binaire:
 pour Opensuse et Ubuntu:
 > make
 > ./zappy_client