# wifi-activity-indicator-pktchip
#### What does this do?
Reads TX_BYTES/RX_BYTES on wlan0 and writes 0/1 to `/sys/class/leds/chip:white:status/brightness` and stays in daemon mode.

Will automatically boot up on wifi uplink and die/set brightness to 0 when wifi disconnects/disabled, for this to work, please place 10wifiled in `/etc/NetworkManager/dispatcher.d`.

#### To build:
`gcc -Wall -O2 -o wifi-ind wifi-ind.c`

#### Notes:

Please do chmod +x on 10wifiled.

The default location of wifi-ind is `/usr/local/bin`, for the 10wifiled script to work, the file needs to be there.

#### Misc:

This code will probably work in whatever device with accessible LEDs if you do some tweaks.

Also please keep in mind, that in this particular Pocket CHIP case I use nmtui to configure my networks.