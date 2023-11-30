# !/bin/bash
xrandr --output eDP --brightness $(echo "$(xrandr --verbose | grep -m 1 -i brightness | cut -f2 -d ' ') + 0.05" | bc)
