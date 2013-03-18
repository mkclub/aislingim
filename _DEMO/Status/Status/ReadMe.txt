Demo that illustrates all necessary steps to do except for SignIn to appear for other users as online user.
Based on call application.

After running this demo and specifying correct credentials, you should see tons of XML,
ending with presense information from all your online-contacts. 

Check out other client, you should be online from here as well.

To make this app work, please, put 
expat.lib
libjingle.lib

from libjingle to the SignIn\libjingle\lib

after that everything should build as usually (if you put release version of libs, build release, debug -- build debug).

We're thinking about ways to make it work without any additional moves, but we're not there yet.

Also, if you have/had other issues trying to build/run this code, inform us.