**FGCom:**<br />
[FGCom](http://squonk.abacab.org/dokuwiki/fgcom) is a command line, voip, virtual radio software built around [Asterisk](http://www.asterisk.org/). It works together with the [FlightGear](http://flightgear.org) flight simulator to bring realistic radio communications to your FlightGear sessions. There are some FlightGear wiki articles on fgcom [here](http://wiki.flightgear.org/index.php/FGCOM), [here](http://wiki.flightgear.org/index.php/FGCOM_for_Windows), and [here](http://wiki.flightgear.org/index.php/User:Zexe).

**FGComGui:**<br />
FGComGui is a simple gui front end to fgcom, which aims to make using fgcom easy and friendly. It has currently been tested on Linux and Windows operating systems, with plans for a Mac version at some point in the (hopefully near) future.

**Windows:**<br />
Users can find prebuilt binary packages on the Downloads tab(grab the newest). These come with everything needed to start using fgcomgui/fgcom. There is no installer currently, just unzip somewhere and run. See the [Windows installation guide](Windows_Installation.md) for more detailed installation instructions.

**Linux:**<br />
Users will have to build from source, see the Source tab for instructions how to get it from svn. Currently there is a simple scons script for building, known to work on Ubuntu Intrepid, you may need to adjust the SConstruct file for your system. A better build system will be coming soon, probably using cmake. You will also need to have installed fgcom. There is a patch for fgcom on the Downloads tab that is recommended, though not entirely necessary. Among other things the patch flushes the stdout/stderr of fgcom after writing so fgcomgui is able to read it in realtime. See the [Linux installation guide](Linux_Installation.md) for more detailed instructions.

**Documentation:**<br />
Documentation can be acessed from the help menu. (Help -> Documentation)

**Screenshots:**<br /><br />
The main window.<br />
[![](http://farm3.static.flickr.com/2694/4272346403_1db8165819_o.png)](http://www.flickr.com/photos/jmburbach/4272346403/sizes/o)
<br /><br />
The configuration dialog, with extra, less needed settings.<br />
[![](http://farm3.static.flickr.com/2764/4272346429_efd3df21a4_o.png)](http://www.flickr.com/photos/jmburbach/4272346429/sizes/o)
<br /><br />
FGComGui in the system tray / notification area.<br />
[![](http://farm3.static.flickr.com/2743/4273089862_2a874576fb_o.png)](http://www.flickr.com/photos/jmburbach/4273089862/sizes/o)
[![](http://farm3.static.flickr.com/2731/4273089842_7c1c669e94_o.png)](http://www.flickr.com/photos/jmburbach/4273089842/sizes/o)