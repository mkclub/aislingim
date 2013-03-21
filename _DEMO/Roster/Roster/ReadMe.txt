Demo app that allows to login and see changing list of contacts with actual statuses.
 Used resources: 
   - "call" project from libjingle source.

To make this app work, please, put 
expat.lib
libjingle.lib

from libjingle to the SignIn\libjingle\lib

after that everything should build as usually (if you put release version of libs, build release, debug -- build debug).

We're thinking about ways to make it work without any additional moves, but we're not there yet.

Also, if you have/had other issues trying to build/run this code, inform us.