#!/bin/bash
# po_merge.sh - written by Andreas Loibl <andreas@andreas-loibl.de>
cd po
for POFILE in *.po
do
    msgmerge -o $POFILE.new $POFILE messages.pot
    if test -s $POFILE.new; then
        grep -v "\"POT-Creation" $POFILE.new > $POFILE.new.2
        grep -v "\"POT-Creation" $POFILE > $POFILE.new.1
        if diff $POFILE.new.1 $POFILE.new.2; then
            rm $POFILE.new
        else
            mv $POFILE.new $POFILE
        fi
        rm -f $POFILE.new.1 $POFILE.new.2
    fi
done
cd ..
