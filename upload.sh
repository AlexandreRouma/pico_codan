#!/bin/sh

BUILD_DIR=`dirname $0`/build

sudo picotool reboot -f -u
sleep 1
sudo picotool load -f -x $BUILD_DIR/firmware.uf2
