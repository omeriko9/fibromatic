#!/bin/bash
if [[ ! -f /tmp/n ]]; then
    touch /tmp/n
    cd ~/shared/neighbour && node start.js
fi
