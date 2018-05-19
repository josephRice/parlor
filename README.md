# Parlor

a native webkit-gtk frontend for [The Lounge irc client](https://thelounge.chat).  

![screen shot](https://github.com/josephRice/parlor/raw/master/screenshots/Screenshot_1.png "screen shot 1")


 You will have to install the lounge by following their current [install](https://thelounge.chat/docs/getting_started/install.html) instructions.

IE.
```
$ [sudo] npm -g install thelounge
```

This was developed and tested on Ubuntu Linux, however it should compile on any posix os that webkit-gtk and webview libraries can compile on.  The code currently makes use of open_memstream function which is a GNU extension, so it may not compile with c libs that do not support ```#define _GNU_SOURCE```. 

## Cloning istructions

This project uses git submodules to pull in the [webview]() project as a sub directory.   You will need to recursively pull down the sub module with.

```
$ git clone --recursive https://github.com/josephRice/parlor.git
```

If you already cloned with out the --recursive flag not to worry.  From your cloned project directory run the following.

```
$ git submodule init
$ git submodule update --recursive --remote --init
```

## Dependancies

 * build tools 
   * c compiler
   * cmake
   * gnu make
 * gtk+-3.0
 * webkit2gtk-4.0

on Ubuntu 18.04

```
$ sudo apt install build-essential cmake libgtk-3-0 libgtk-3-dev libwebkit2gtk-4.0-37 libwebkit2gtk-4.0-dev
```



## build instructions

```
$ mkdir ./build
$ cd ./build
$ cmake ..
$ make
```
## install instructions

from within the ./build directory

```
$ sudo make install
```

### Install contents

 * parlor to /usr/bin
 * parlor.desktop to /usr/share/applications
 * parlor.png to /usr/share/icons/

## Usage

parlor will attempt to launch the lounge if it is not already running.  Please make sure that the lounge is properly installed and you have configured a user.   Parlor assumes that you will be running on the default port, and you can browse to https://localhost:9000/.  Currently; if you want to run the lounge on a differnt port or URL, the source code will have to modified (a planned future change).  

From the commandline after running make install:

```
$ /usr/bin/parlor
```

From Gnome,KDE,etc...; If your Desktop environment is sane and recognizes .desktop files, you should find Parlor in your applications list/launcher.  
