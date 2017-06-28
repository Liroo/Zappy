##
## Makefile for make in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
## 
## Made by Lucas
## Login   <lucas.onillon@epitech.eu>
## 
## Started on  Sun Jun 25 22:50:07 2017 Lucas
## Last update Wed Jun 28 01:35:41 2017 Thomas
##

TARGET	 = zappy_client

CC	 = g++

SRC	 = main.cpp					\
	   core.cpp					\
	   LTexture.cpp					\
	   splashScreen.cpp				\
	   connectClient.cpp

CPPFLAGS = -Iinclude -std=c++11 -Ilib_irrlicht -I/usr/X11R6/include -Iirrklang
CXXFLAGS = -W -Wall -std=c++11 -ansi -Iinclude -Wno-unused-parameter -pedantic
LDFLAGS	 = -lIrrlicht -lpthread -std=c++11
LDFLAGS += -IrrKlang

SRCDIR   = src
OBJDIR   = obj

SOURCES  := $(addprefix src/, $(SRC))

OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

rm       = rm -rf
mkdir    = mkdir -p

$(TARGET): $(OBJECTS)
	@$(CC) $(CPPFLAGS) -o $@ $(OBJECTS) $(CXXFLAGS) $(LDFLAGS)
	@echo $(TARGET)" compiled !"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(mkdir) $(OBJDIR)
	@$(CC) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

all	 : all_linux

all_linux: LDFLAGS += -L/usr/X11R6/lib$(LIBSELECT) -lGL -lXxf86vm -lXext -lX11 -lXcursor

all_linux : $(TARGET)

clean	: clean_linux

clean_linux:
	@$(rm) $(OBJDIR)
	@echo "Binary files deleted"

fclean	: clean
	@$(rm) $(TARGET)
	@echo "Binary and executable files are deleted"

re	: fclean all

.PHONY: all clean clean_linux fclean re

#multilib handling
ifeq ($(HOSTTYPE), x86_64)
LIBSELECT=64
endif
#solaris real-time features
ifeq ($(HOSTTYPE), sun4)
LDFLAGS += -lrt
endif
