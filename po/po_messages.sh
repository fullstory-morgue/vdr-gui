#!/bin/bash
# po_messages.sh - written by Andreas Loibl <andreas@andreas-loibl.de>
SOURCES="vdr-start-menu/vdr-* xine-client/vdr-* script/vdr-*"
# Create messages.pot
{
for SOURCE_FILE in $SOURCES
do
    bash --dump-po-strings $SOURCE_FILE
done
} | msguniq > po/messages.pot
