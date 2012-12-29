# Arduino WebServer

## Overview

A simple web server on an Arduino with an Ethernet Shield on top.

I implement a simple task like turning on/off a device.
With that in mind you can do whatever you want.

### Setup

* Ethernet Shield on top of the Arduino UNO
* Our device (led for testing) at pin 2
* Setup connected to a router or switch

###Changes on the sketch

To run the sketch correctly you should trim it a bit.

* Change the MAC adress to the one behind your Ethernet Shield
* Change the IP to match the IP given by flashing File>Examples>Ethernet>DhcpAddressPrinter (Arduino Software)
* Host the `a.css` file somewhere in the network and change the link in the sketch with the correct one.

Done!
=====

