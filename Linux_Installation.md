

# Introduction #
This guide will walk you through installing fgcom and fgcomgui on a Linux system.

# Installing FGCOM #
You will first need to install the command line FGCOM program. For FGCOM to work properly with FGComGui the functionality and bug fix patch **must** be applied before building and install FGCOM. Even if you do not plan on using FGComGui, it is **highly** recommended you apply this patch to your FGCOM, as it contains bug fixes and extra functionality.

## Getting The Source ##
You can obtain the FGCOM source code via svn by running the following command in a terminal. This will download and save the source code into a directory call fgcom.
```
svn co https://appfgcom.svn.sourceforge.net/svnroot/fgcom/trunk fgcom
```

## Patching FGCOM ##
After you have retrieved the fgcom source from svn it is time to download and apply the FGComGui functionality and bug fix patch. It is available from the Downloads page, and is named **fgcomgui-fgcom\_MMDDYYYY.diff**, with MMDDYYYY being the date of the patch. Download the newest one available and save it in the fgcom directory created when you checked out the fgcom source code.

Now in a terminal, from inside the fgcom directory, apply the patch with the following command.
```
patch -p0 < fgcomgui-fgcom_MMDDYYYY.diff
```

## Satisfying Dependencies ##
FGCOM includes most of its dependencies already, but by default there are two external you must satisfy to build FGCOM. These are [plib](http://plib.sourceforge.net) and [simgear](http://www.simgear.org). The FGComGui patch for FGCOM removes the dependency on simgear however, so you only need satisfy the plib dependency. Both of these are available on many Linux distributions as plib-dev and simgear-dev for example, or they can be installed from source if necessary.

## Building And Installing ##
Once you have installed the necessary dependencies we can build and install fgcom. In a terminal, from inside the fgcom/src directory, run the following commands to build and install fgcom. Installs to /usr/local by default.
```
make
sudo make install
```

# Installing FGComGui #
## Getting The Source ##
The fgcomgui source code is available from svn, run the following command in a terminal to retrieve it.
```
svn co http://fgcomgui.googlecode.com/svn/trunk/ fgcomgui
```

## Satisfying Dependencies ##
FGComGui's major dependency is Qt4, which is quite common, and often already installed on many Linux systems. You will need to have installed the development files for Qt4, available as **libqt4-dev** on many Linux distributions. The only other dependency is SCons, the current build system used to build the program.

## Building And Installing ##
Currently fgcomgui uses a simple SCons build system, which should work out of the box on Ubuntu like systems. You may need to tweak the paths for the Qt4 files and programs in the SConstruct file on other systems.

To build and install fgcomgui, run the following command from the fgcomgui directory.
```
scons
sudo scons install
```

By default fgcomgui will install to /usr/local, but can be changed by using prefix option when running scons. For example.

```
scons prefix=/wherever/you/want
sudo scons install
```

When installing to non-standard directories however, it should be noted that desktops will most likely not be able to find the installed .desktop file and icons, and not be available in your menu or other places.