#!/bin/bash

######
# Chercher tous les fichiers .song sur la clef USB
# Les copiers dans /home/ubuntu/songs
######
export DISPLAY=":0"
notify-send "Copying new songs... Please wait."
cp /media/song_usb/*.song /home/ubuntu/songs
sync
umount /media/song_usb
notify-send "Copying done, you can safely remove the USB key"
