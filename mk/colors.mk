# Colors

COLOR_SUPPORTED=	1

ifeq ($(COLOR_SUPPORTED), 0)
# Colors definitions
CLEAR=

# Regular
BLACK_R=
RED_R=
GREEN_R=
YELLOW_R=
BLUE_R=
PURPLE_R=
CYAN_R=
WHITE_R=

else

# Colors definitions
CLEAR= \e[0m

# Regular
BLACK_R= \e[0;30m
RED_R= \e[0;31m
GREEN_R= \e[0;32m
YELLOW_R= \e[0;33m
BLUE_R=	\e[0;34m
PURPLE_R= \e[0;35m
CYAN_R=	\e[0;36m
WHITE_R= \e[0;37m
endif
