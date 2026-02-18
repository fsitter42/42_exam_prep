#!/bin/bash
# Startet eine neue tmux-Session namens 'minishell'
tmux new-session -d -s popen

# Splitte das Fenster horizontal (ergibt oben/unten)
tmux split-window -v

# Splitte das untere Fenster vertikal (ergibt unten links/unten rechts)
tmux split-window -h

# Verbinde dich mit der Session
tmux attach-session -t popen
