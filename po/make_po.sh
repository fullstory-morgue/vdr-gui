#!/bin/bash
# make_po.sh - written by Andreas Loibl <andreas@andreas-loibl.de>
PO_NAME=$1
cd po
for i in *.po;
do
  PO_LANG=${i/.po/}
  mkdir -p $DESTDIR/usr/share/locale/$PO_LANG/LC_MESSAGES
  msgfmt -o $DESTDIR/usr/share/locale/$PO_LANG/LC_MESSAGES/$PO_NAME $i
done
cd ..
