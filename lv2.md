# Extension #
be carefull, the lv2 spec, and those extension are not stable nor beta.

### lv2midi ###
add a timestamped midi data type to lv2 port

### lv2gtk2gui ###
embedable gui extension using gtk, communication between the engine and the host is defined by the host. The gui is a separated library

### dynparams ###
allow to have add/remove port at runtime

### instrument ###
allow to exchange datas and files.
the host is responsible to store file into the project directory, and or to copy the file from one computer to another

# Plugins #

## Input ##
### Klaviatur ###
a midi keyboard
### Trilobyte ###
a midi matrix sequencer
### Trilobeat ###
a midi drum sequencer

### Butinator ###
a playlist editor (to use with soulrider)

## Instruments ##
### soulrider ###
a virtual turntable with pitch/loop

### Azr3 ###
### euphoria ###
### sineshaper ###

## Effect ##
### tronsonator ###
a 4 channels dj mixer with a crossfader, gain and volume for each channel
### arpeggiator ###
midi arpeggiator
### phase-distortion-osc ###
phase distortion oscilator

## Misc ##
### math-functions ###
math functions as lv2 plugins, for audio and control port
### math-constants ###
math constants like pi pi/2, ...
### control2midi ###
control value sent over a midi output port
### audio\_identity ###
output=input
### midi\_identity ###
output=input