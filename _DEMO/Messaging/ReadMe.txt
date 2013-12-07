Demo that illustrates how user can login and receive messages from other users.
Based on call application.

After running this demo and specifying correct credentials, you should be able to receive messages from other contacts.

To make this app work, please, put 
expat.lib
libjingle.lib

from libjingle project directory (trunk\build\[Release|Debug]\lib) 
to the libjingle_libs[Debug | Release] in aislingim project root.

after that everything should build as usually (if you put release version of libs, build release, debug -- build debug).

We're thinking about ways to make it work without any additional moves, but we're not there yet.

Also, if you have/had other issues trying to build/run this code, inform us.