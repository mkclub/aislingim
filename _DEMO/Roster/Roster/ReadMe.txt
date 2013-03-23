Demo app that allows to login and see changing list of contacts with actual statuses.
 Used resources: 
   - "call" project from libjingle source.

To make this app work, please, put 
expat.lib
libjingle.lib

from libjingle project directory (trunk\build\[Release|Debug]\lib) 
to the libjingle\lib inside this project 
or to aislingim\libjingle_libs\[Debug | Release] (it will be copied the mentioned above folder in pre-build event).

after that everything should build as usually (if you put release version of libs, build release, debug -- build debug).

We're thinking about ways to make it work without any additional moves, but we're not there yet.

Also, if you have/had other issues trying to build/run this code, inform us.