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
CLEAR= \033[0m

# Regular
BLACK_R= \033[0;30m
RED_R= \033[0;31m
GREEN_R= \033[0;32m
YELLOW_R= \033[0;33m
BLUE_R= \033[0;34m
PURPLE_R= \033[0;35m
CYAN_R= \033[0;36m
WHITE_R= \033[0;37m
endif
