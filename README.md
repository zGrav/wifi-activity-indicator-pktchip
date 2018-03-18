# wifi-activity-indicator-pktchip
#### What does this do?
Reads TX_BYTES/RX_BYTES on wlan0 and writes 0/1 to `/sys/class/leds/chip:white:status/brightness` and stays in daemon mode.

Will automatically boot up on wifi uplink and die/set brightness to 0 when wifi disconnects/disabled, for this to work, please place up-wifi-led and down-wifi-led in /etc/network/if-up.d and /etc/network/if-down.d.

#### To build:
`gcc -Wall -O2 -o wifi-ind wifi-ind.c`

#### Misc:

This code will probably work in whatever device with accessible LEDs if you do some tweaks.