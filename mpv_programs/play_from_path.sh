#!/bin/bash

# C++ übergibt zwei Parameter
USER_VIDEO=$1
DEFAULT_VIDEO=$2

# 1. Das aktuell laufende Default-Video beenden
#pkill mpv

# 2. Das User-Video im Vordergrund abspielen (C++ wartet hier)
#DISPLAY=:0 mpv --no-osc --no-osd-bar "$USER_VIDEO"

# 3. Sobald das Video fertig ist, das Default-Video wieder im Hintergrund starten
#DISPLAY=:0 mpv --loop=inf --no-osc --no-osd-bar "$DEFAULT_VIDEO" &



#fuer cli system

# 2. Das User-Video im Vordergrund abspielen (C++ wartet hier)
#mpv --vo=drm --hwdec=auto --hwdec-codecs=all --no-osc --no-osd-bar "$USER_VIDEO"

# 3. Sobald das Video fertig ist, das Default-Video wieder im Hintergrund starten
#mpv --vo=drm --hwdec=auto --hwdec-codecs=all --loop=inf --no-osc --no-osd-bar "$DEFAULT_VIDEO" &


SOCKET="/tmp/mpv_socket"

# 1. Loop für das aktuelle Video ausschalten
#echo -e '{ "command": ["set_property", "loop-file", "no"] }\n' | socat - "$SOCKET"

# 2. Sofort das User-Video abspielen (ersetzt das aktuelle)
#echo -e '{ "command": ["loadfile", "'"$USER_VIDEO"'", "replace"] }\n' | socat - "$SOCKET"

# 3. Das Default-Video hinten anhängen und als Option "loop-file=inf" mitgeben
#echo -e '{ "command": ["loadfile", "'"$DEFAULT_VIDEO"'", "append", "loop-file=inf"] }\n' | socat - "$SOCKET"


# 0. Globales Looping explizit auf 'no' setzen, um Altlasten zu löschen
echo '{ "command": ["set_property", "loop-file", "no"] }' | socat - "$SOCKET"

# 1. Playlist komplett löschen (sicherstellen, dass wir bei Null anfangen)
echo '{ "command": ["playlist-clear"] }' | socat - "$SOCKET"

# 2. Erstes Video laden
echo '{ "command": ["loadfile", "'"$USER_VIDEO"'", "replace"] }' | socat - "$SOCKET"

# 3. Zweites Video mit Loop-Option anhängen
echo '{ "command": ["loadfile", "'"$DEFAULT_VIDEO"'", "append", "loop-file=inf"] }' | socat - "$SOCKET"