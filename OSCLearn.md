# Introduction #

This page is a Draft for a OSC-based protocol which will allow, in the first hand, independent programs to query  a list of the OSC parameters that application supports. In other hand, it will allow a single program to manage the so appreciated 'Learn' feature for all the application that supports this protocol.

# Overview #

## Pameters querying ##
A special message is sent to the OSC application, with a return address. The application must send back a list of all the available path, with some mapping hints for each to the return address.

## Learn ##
A new type of zeroconf service is defined, like "_osc._udp._learn". Then the application query avahi/bonjour/... services to find a service of this type. Each time a button is clicked, a fader is moved, and so on, the application sends an OSC message to the learn service containing the address of the concerned parameter (osc://1.2.3.4:42/mixer2/pan5) and some mapping hints (trigger, note, CC, etc). So the learn application can know which parameter is going to be learned, he can listen on all the devices he's monitoring (most of time he will monitor all the devices) and then map the first event it receives with the last address who was sent to him via the learn protocol._

## Implementation ##
It will be implemented as a patch for liblo or as another library using liblo.

# ODL RFC (draft) #

## Foreword ##

### Introduction ###

ODL works on top of OSC, so you might consider reading http://www.cnmat.berkeley.edu/OpenSoundControl/OSC-spec.html if you're not familiar with OSC.

Although it is not required, ODL can takes advantage of the ZeroConf protocol (http://www.zeroconf.org/), branded '_Bonjour_' by Apple. It is available on Apple, Windows (_Bonjour_), and most Linux/Unix distributions (_Avahi_).

The ODL protocol is based on 'server-server' (peer-to-peer) architecture, for the learn part, and client-server architecture for the discovery. It consists as 2 sets of OSC messages, one for discovery, the other for learn. The last part of this document contains recommendations about the use of zeroconf to improve simplicity of use for the final user.

### Conventions ###

When describing an OSC message path, 

&lt;FOO&gt;

 will stand for the path of the foo osc server (osc://192.42.42.42:42042/ for example)

When describing the format of an OSC message, the following conventions will be used :
  * I, OSC's 32 bit int.
  * T, OSC's time stamp.
  * F, OSC's float.
  * S, OSC's string.
  * B, OSC's blob.
So "TIIF" indicates a message containing in this order: a time stamp, 2 integers, and a float.

## Discovery ##

In this subsection, 

&lt;Discover&gt;

 and 

&lt;Discovered&gt;

 will stand respectively for the path of the server which tries to obtain the list of the supported messages and the server which is being queried for it's OSC message interface.

This part of the protocol is made of the following queries and answer:

  * Query : 

&lt;Discovered&gt;

/discover/list**: message format "S" : this OSC message is a string representing the path of the server & message to which send the message's list back.**

  * Answer : 

&lt;Discover&gt;

/some/path**: this path, including the hostname/address and port of the discovering server is submitted by the discovering server inside the preceding message. : message format "I ISSS [[ISSS](ISSS.md) ...]" : the first int indicates the number of block  ('discovered' messages) this message includes. Each following block is made of 3 mandatory components and an optional one.
    * "Sss" : the first string is the path of the message, without the leading server address and port.
    * "sSs" : the second string describes the format of the message in the same syntax as this document : I for int, T for time stamp, F for float, etc.
    * "ssS" : a string to be displayed to the user which describe what the message controls.**

## Learn ##

The learn part of the protocol allow you to easily bind any part of any controller (button, fader, x-y, etc of midi controller, mouse, keyboard, ...) to any parameters you see on your screen or on your hardware machine that supports this protocol.

In order to achieve this goal, in an environment with many piece of software running in their own processes, we have an application that keep track of the OSC paths being tuned, and manage the controller. When asked, it can bind the physical element being moved with the last OSC paramater which as been changed in the screen (or in a piece of hardware that support OSC as input)

If we want to be able to know which was the last tuned parameter (the 'current' parameter), every application who support this protocol must announce that it is being tuned : not announcing the value of the parameter but the path of the parameter, the announce is made only one by parameter (if the same parameter it tweaked twice without changing another parameter between only one announce is made in order to reduce bandwidth usage). Either the announce is made to a know OSC server supporting the learn protocol, or it sends announces on all OSC server supporting the learn protocol discovered via ZeroConf (see the next section). The second way is preferred. The way of binding a physic control on an OSC path is not covered by this document and is implementation specific.



&lt;learn&gt;

 is the address of an osc learning service


&lt;bar&gt;

 is the address of a server which support the learn protocol.

Format of the Announce :

"SS[S...]" :
  * the first string is the path of the parameter which is being tuned on the announcing server, include the server's address and port.
  * the second string is the format of the message being announced using the same conventions as in this document.
  * these two parts are necessary, this one is optional. In the last part of the osc message, the announce contains mapping hints about the parameter (float range, int range, timestamps format, ...). One string per message item, empty string if any hint. Hints format is explained in the following paragraph.

Hints format : work in progress.

## ZeroConf ##

In order to allow all ODL software to find each others we highly recommend that you use the following types and subtypes of service when registering your OSC server on a ZeroConf server :
  * Types of service :
    * `"_osc._udp"` : UDP-based OSC server.
    * `"_osc._tcp"` : TCP-based OSC server.
  * Subtypes :
    * `none` : simple OSC server.
    * `"_learn"` : the OSC server is a learn server (it supports learn part of ODL).
    * `"_discovery"` : the OSC server support the query mechanism.


Please send me any suggestions and/or remarks by mail :

Julien BALLET <elthariel 

&lt;at&gt;

 gmail 

&lt;dot&gt;

 com>
L.A.E. (EPITA/EPITECH Audio Lab)