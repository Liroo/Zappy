#!/bin/sh

# This is a way to install program on computer
# in addition of this repository

usage_and_exit () {
  echo "Usage: install.sh | install   | DIRECTORY" >&2
  echo "                  | uninstall |" >&2
  exit 1
}

# define binaries name
SERVER_DIR="./server"
SERVER="server"

CLIENT_DIR="./ai"
CLIENT="client"

# install the client and server by copying then in the directory passed as parameter
install () {
    cp $SERVER_DIR/$SERVER $1
    cp $CLIENT_DIR/$CLIENT $1

    echo "Install done !"
}

# uninstall by deleting the binaries from the directory
uninstall () {
    rm -f $1/$SERVER
    rm -f $1/$CLIENT

    echo "Uninstall done !"
}

# check if argument count is 2
if [ "$#" -ne 2 ]; then
  usage_and_exit
fi

# check if directory is valid
if ! [ -e "$2" ]; then
  echo "$2 not found" >&2
  exit 1
fi
if ! [ -d "$2" ]; then
  echo "$2 not a directory" >&2
  exit 1
fi

# check option wanted passed from parameter
if [ "$1" = "install" ]; then
  install $2
elif [ "$1" = "uninstall" ]; then
  uninstall $2
else
  usage_and_exit
fi;
