# camisado
Linux kernel module that sends a UDP packet without being seen by code running in userspace.

Uses the Kernel's netpoll API to send a packet at a low level (invisible to tcpdump/pcap/wireshark etc)

This doesn't work for all network interfaces (no wireless, no loopback, no USB ethernet etc)

Edit the source file to include the correct IP addresses and then start a listener on the remote side
```
nc -l -u -p 123
```
Insert the Kernel module and the text should be seen on the remote side. 
