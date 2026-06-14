#!/bin/bash
# $1 ist der erste Parameter, den C++ übergibt (der Pfad zum Default-Video)
DEFAULT_VIDEO=$1

# Startet das Video im unendlichen Loop im Hintergrund
#DISPLAY=:0 mpv --loop=inf --no-osc --no-osd-bar "$DEFAULT_VIDEO" &


# Startet das Video im unendlichen Loop im Hintergrund (ohne Desktop)
#mpv --vo=drm --hwdec=auto --hwdec-codecs=all --loop=inf --no-osc --no-osd-bar "$DEFAULT_VIDEO" &


SOCKET="/tmp/mpv_socket"

# Alte Prozesse und Sockets aufräumen
pkill -f mpv
rm -f "$SOCKET"

# mpv starten und den IPC-Server aktivieren
#mpv --vo=drm --hwdec=auto --hwdec-codecs=all --loop-file=yes --really-quiet --no-osc --no-osd-bar --input-ipc-server="$SOCKET" "$DEFAULT_VIDEO" &


#erster optimierter versuch
#mpv --vo=drm --hwdec=v4l2m2m-copy --vd-lavc-dr=no --video-sync=display-resample --loop-file=yes --really-quiet --no-osc --no-osd-bar --input-ipc-server="$SOCKET" "$DEFAULT_VIDEO" &


# Dem System Zeit geben, den Socket zu erstellen
#sleep 0.5

#disown


export XDG_RUNTIME_DIR=/run/user/$(id -u)
export DISPLAY=:0

# Startet mpv im Vollbild, randlos, immer im Vordergrund
mpv --input-ipc-server="$SOCKET" \
    --vo=gpu \
    --hwdec=v4l2m2m \
    --ao=alsa \
    --audio-device='alsa/sysdefault:CARD=Headphones' \
    --fs \
    --no-border \
    --loop-file=inf \
    --input-vo-keyboard=no \
    --volume=80 \
    "$DEFAULT_VIDEO"