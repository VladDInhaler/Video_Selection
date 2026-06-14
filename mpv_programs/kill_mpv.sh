#!/bin/bash

#killall mpv
PIPE="/tmp/mpv_input"

# mpv sauber sagen, dass es sich schließen soll
echo "quit" > "$PIPE" 2>/dev/null

# Sicherheitshalber aufräumen
sleep 0.2
pkill -f mpv
rm -f "$PIPE"