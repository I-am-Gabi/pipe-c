# C PIPE

This is the code make for Posix Class, a small set of code to handle with process
and pipe. 

Run
---

There is a script ```execute.sh``` in the root directory. You can run it, but probably will be 
necessary change the permission (making the file readable, writable and executable by everyone). 

    $ chmod 777 execute.sh
    $ ./execute.sh
    
After make this, you can go to the folder ```bin/``` and run the executable. For example:
    
    $ ./ring
    

Protocol
---------

1. The station 0 will begin asking for the data package (content, destination, etc).
2. The package will be sending to the destination, and your token will be BUSY
3. When the package arrived at your destination, it will change the token to ACK 
4. When the package arrived at your origin station, it will change the token to 
FREE and send to the next stations.
5. After, the user will say if he wants send a new package or not.
    5.a If he answers yes, we go the the step 1.
    5.b If he doesn't want, the package doesn't change and keep in movement.