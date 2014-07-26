GiveMeRoot
==========

Kernel module to set root privileges to any given process (suid = uid = fsuid = euid = 0)

    
Dependencies
=======

In order to compile the kernel module you should have the latest version of your Linux kernel headers.

On Ubuntu/Debian you can install them using:

    sudo apt-get install linux-headers-$(uname -r)


Installation and use
============

* Compile givemeroot module



		$ make



* Find the pid of the process you want to give root privileges



		$ ps aux | grep vim
		myuser  5166  1.3  0.1 249988 10980 pts/12   Sl+  15:15   0:00 vim



* Insert the module into the kernel with pid parameter



		$ insmod givemeroot.ko pid=5166




Unload kernel module
============

	$ rmmod givemeroot

